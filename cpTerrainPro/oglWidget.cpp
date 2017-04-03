
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
    glClearColor(0, 0, 1, 1);

    // Load Shaders (0th element in the shader list is NULL)
    addShader(":/shaders/cube.vert", ":/shaders/cube.frag", "Vertex,Color,Normal,Texture");

    crateShader = shader[1];
    crateShader->link();

    crateShader->bind();
    crateShader->setUniformValue("tex", 0);
    m_projMatrixLoc = crateShader->uniformLocation("ProjectionMatrix");
    m_mvMatrixLoc = crateShader->uniformLocation("ModelViewMatrix");
    m_normalMatrixLoc = crateShader->uniformLocation("NormalMatrix");
    m_vMatrixLoc = crateShader->uniformLocation("ViewMatrix");
    m_lightPosLoc = crateShader->uniformLocation("Position");

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

    crateShader->release();
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

    doProjection();
    doView();
    QVector4D lpos = doLight();

    setCam();

    m_world.setToIdentity();
    m_world.rotate(ph, 1, 0, 0);
    m_world.rotate(th, 0, 1, 0);

    QOpenGLVertexArrayObject::Binder vaoBinder(&cubeVAO);
    crateShader->bind();
    crateShader->setUniformValue(m_projMatrixLoc, m_proj);
    crateShader->setUniformValue(m_mvMatrixLoc, m_camera * m_world);
    QMatrix3x3 normalMatrix = m_world.normalMatrix();
    crateShader->setUniformValue(m_normalMatrixLoc, normalMatrix);
    crateShader->setUniformValue(m_vMatrixLoc, m_world);
    crateShader->setUniformValue(m_lightPosLoc, lpos);


    crateTex->bind();
    //glDrawArrays(GL_TRIANGLES, 0, 36);

    QOpenGLVertexArrayObject::Binder vaoBinder1(&sphereVAO);

    glDrawArrays(GL_TRIANGLES, 0, 684);


    crateShader->release();

}

void oglWidget::resizeGL(int w, int h)
{
    m_proj.setToIdentity();
    m_proj.perspective(45.0f, GLfloat(w) / h, 0.01f, 100.0f);
}

