
#include "oglWidget.h"
#include "particles.h"
#include "cube.h"
#include "sphere.h"

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

    passShader->link();
    passShader->bind();
    m_projMatrixLoc = passShader->uniformLocation("ProjectionMatrix");
    m_mvMatrixLoc = passShader->uniformLocation("ModelViewMatrix");
    m_normalMatrixLoc = passShader->uniformLocation("NormalMatrix");
    m_vMatrixLoc = passShader->uniformLocation("ViewMatrix");
    m_lightPosLoc = passShader->uniformLocation("Position");
//    crateShader->link();
//    crateShader->bind();
//    crateShader->setUniformValue("tex", 0);
//    m_projMatrixLoc = crateShader->uniformLocation("ProjectionMatrix");
//    m_mvMatrixLoc = crateShader->uniformLocation("ModelViewMatrix");
//    m_normalMatrixLoc = crateShader->uniformLocation("NormalMatrix");
//    m_vMatrixLoc = crateShader->uniformLocation("ViewMatrix");
//    m_lightPosLoc = crateShader->uniformLocation("Position");

    // Load Textures
    crateTex = new QOpenGLTexture(QImage(":/textures/crate.png").mirrored());

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

    passShader->release();
}

void oglWidget::setCam()
{
    // Our camera never changes in this example.
    m_camera.setToIdentity();
    m_camera.translate(0, 0, -dim);
}


void oglWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    setCam();
    doProjection();
   // doView();
    QVector4D lpos = doLight();

    QMatrix4x4 view = doView();
    QMatrix4x4 mv = view;
    QMatrix3x3 normalMatrix = mv.normalMatrix();

    QOpenGLVertexArrayObject::Binder vaoBinder(&cubeVAO);
    crateShader->bind();
    crateShader->setUniformValue(m_projMatrixLoc, proj);
    crateShader->setUniformValue(m_mvMatrixLoc, mv);
    crateShader->setUniformValue(m_normalMatrixLoc, normalMatrix);
    crateShader->setUniformValue(m_vMatrixLoc, view);
    crateShader->setUniformValue(m_lightPosLoc, lpos);


    crateTex->bind();
    //glDrawArrays(GL_TRIANGLES, 0, 36);
    crateShader->release();


    QOpenGLVertexArrayObject::Binder vaoBinder1(&sphereVAO);
    passShader->bind();
    passShader->setUniformValue(m_projMatrixLoc, proj);
    passShader->setUniformValue(m_mvMatrixLoc, mv);
    passShader->setUniformValue(m_normalMatrixLoc, normalMatrix);
    passShader->setUniformValue(m_vMatrixLoc, view);
    passShader->setUniformValue(m_lightPosLoc, lpos);
    glDrawArrays(GL_TRIANGLES, 0, 5256);
    passShader->release();
}




