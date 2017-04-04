
#include "oglWidget.h"
#include "particles.h"
#include "cube.h"
#include "sphere.h"
#include "Noise.h"
#include <iostream>

oglWidget::oglWidget(QWidget *parent)
    : CUgl(parent),
      crateShader(0)
{
    cube_size=36;
}

oglWidget::~oglWidget()
{
    cleanup();
}

QSize oglWidget::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize oglWidget::sizeHint() const
{
    return QSize(600, 400);
}


void oglWidget::cleanup()
{
    makeCurrent();
    cubeBuff.destroy();
    delete crateShader;
    crateShader = 0;
    doneCurrent();
}

//
//  Set mode
//
void oglWidget::setMode(int m)
{
   mode = m;
   //  Request redisplay
   update();
}

//
//  Set position
//
void oglWidget::setMsize(int s)
{
   MAP_SCALE = 0.1*s;
   //  Request redisplay
   //InitializeTerrain();
   update();
}

void oglWidget::setHsize(int s)
{
   H_SCALE = 0.1*s;
   //  Request redisplay
   //InitializeTerrain();
   update();
}


void oglWidget::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0, 0, 0, 1);



    // Load Shaders (0th element in the shader list is NULL)
    addShader(":/shaders/cube.vert", ":/shaders/cube.frag", "Vertex,Color,Normal,Texture");
    crateShader = shader[1];
    addShader(":/shaders/pass.vert", ":/shaders/pass.frag", "Vertex,Color,Normal");
    passShader = shader[2];
    addShader(":/shaders/snow.vert", ":/shaders/snow.frag", "Vertex,Color,Normal,Texture,Vel,Start");
    snowShader = shader[3];


    // Load Textures
    crateTex = new QOpenGLTexture(QImage(":/textures/crate.png").mirrored());
    snowflakeTex = new QOpenGLTexture(QImage(":/textures/snowflake.png").mirrored());

    //  Load random texture
    CreateNoise3D(GL_TEXTURE1);

    // Create a VAO and VBO for the cube
    cubeVAO.create();
    QOpenGLVertexArrayObject::Binder vaoBinder(&cubeVAO);
    cube cube1;
    cubeBuff = cube1.getBuffer();


    // Create a VAO and VBO for the sphere
    sphereVAO.create();
    QOpenGLVertexArrayObject::Binder vaoBinder1(&sphereVAO);
    sphere sphere1;
    sphereBuff = sphere1.getBuffer();

    // Create a VAO and VBO for the snow
    snowVAO.create();
    QOpenGLVertexArrayObject::Binder vaoBinder2(&snowVAO);
    particles snow;
    snowBuff = snow.getBuffer();

    // Create a VAO and VBO for the terrain
    //terrainVAO.create();
    //QOpenGLVertexArrayObject::Binder vaoBinder3(&terrainVAO);
    //particles snow;
    //snowBuff = snow.getBuffer();


}


void oglWidget::paintGL()
{
    float t = 0.001*time.elapsed();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    doProjection();
    QVector4D lpos = doLight();

    QMatrix4x4 view = doView();
    QMatrix4x4 mv = view;
    QMatrix3x3 normalMatrix = mv.normalMatrix();

    // Draw Crate
    mv.translate(-2, 0, 0);
    QOpenGLVertexArrayObject::Binder vaoBinder(&cubeVAO);
    crateShader->bind();
    crateShader->setUniformValue("tex", 0);
    crateShader->setUniformValue("ProjectionMatrix", proj);
    crateShader->setUniformValue("ModelViewMatrix", mv);
    crateShader->setUniformValue("NormalMatrix", normalMatrix);
    crateShader->setUniformValue("ViewMatrix", view);
    crateShader->setUniformValue("Position", lpos);
    crateTex->bind();
    glDrawArrays(GL_TRIANGLES, 0, 36);
    crateTex->release();
    crateShader->release();

    // Draw Sphere
    mv.translate(4, 0, 0);
    QOpenGLVertexArrayObject::Binder vaoBinder1(&sphereVAO);
    passShader->bind();
    passShader->setUniformValue("ProjectionMatrix", proj);
    passShader->setUniformValue("ModelViewMatrix", mv);
    passShader->setUniformValue("NormalMatrix", normalMatrix);
    passShader->setUniformValue("ViewMatrix", view);
    passShader->setUniformValue("Position", lpos);
    glDrawArrays(GL_TRIANGLES, 0, 5256);
    passShader->release();

    // Draw Snow
    mv.translate(-2,0,0);
    QOpenGLVertexArrayObject::Binder vaoBinder2(&snowVAO);
    snowShader->bind();
    snowShader->setUniformValue("tex", 0);
    snowShader->setUniformValue("ProjectionMatrix", proj);
    snowShader->setUniformValue("ModelViewMatrix", mv);
    snowShader->setUniformValue("time",t);
    snowShader->setUniformValue("dim",dim);
    snowShader->setUniformValue("Noise3D",1);
    //  Set particle size
    glPointSize(6);
    glEnable(GL_POINT_SPRITE);
    glTexEnvi(GL_POINT_SPRITE,GL_COORD_REPLACE,GL_TRUE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE);
    glDepthMask(0);
    //  Draw arrays
    snowflakeTex->bind();
    glDrawArrays(GL_POINTS,0,900);
    glDisable(GL_POINT_SPRITE);
    glDisable(GL_BLEND);
    glDepthMask(1);
    snowflakeTex->release();
    passShader->release();


    // Draw Terrain


}




