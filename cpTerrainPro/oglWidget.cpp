
#include "oglWidget.h"
#include "particles.h"

oglWidget::oglWidget(QWidget *parent)
    : CUgl(parent),
      m_xRot(0),
      m_yRot(0),
      m_zRot(0),
      m_program(0)
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

static void qNormalizeAngle(int &angle)
{
    while (angle < 0)
        angle += 360 * 16;
    while (angle > 360 * 16)
        angle -= 360 * 16;
}

void oglWidget::setXRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != m_xRot) {
        m_xRot = angle;
        emit xRotationChanged(angle);
        update();
    }
}

void oglWidget::setYRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != m_yRot) {
        m_yRot = angle;
        emit yRotationChanged(angle);
        update();
    }
}

void oglWidget::setZRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != m_zRot) {
        m_zRot = angle;
        emit zRotationChanged(angle);
        update();
    }
}

void oglWidget::cleanup()
{
    makeCurrent();
    m_logoVbo.destroy();
    delete m_program;
    m_program = 0;
    doneCurrent();
}

void oglWidget::initializeGL()
{
    connect(context(), &QOpenGLContext::aboutToBeDestroyed, this, &oglWidget::cleanup);

    initializeOpenGLFunctions();
    glClearColor(0, 0, 0, 1);

    addShader(":/shaders/cube.vert", ":/shaders/cube.frag", "Vertex,Color,Normal,Texture");
    m_program = shader[1];
    m_program->link();

    m_program->bind();
    m_program->setUniformValue("tex", 0);
    m_projMatrixLoc = m_program->uniformLocation("ProjectionMatrix");
    m_mvMatrixLoc = m_program->uniformLocation("ModelViewMatrix");
    m_normalMatrixLoc = m_program->uniformLocation("NormalMatrix");
    m_vMatrixLoc = m_program->uniformLocation("ViewMatrix");
    m_lightPosLoc = m_program->uniformLocation("Position");

    //
    //  Cube Vertexes
    //
    const float cube_data[] =  // Vertex data
    {
    //  X  Y  Z  W   Nx Ny Nz    R G B   s t
       //  Front
       +1,+1,+1,+1,   0, 0,+1,   1,0,0,  1,1,
       -1,+1,+1,+1,   0, 0,+1,   1,0,0,  0,1,
       +1,-1,+1,+1,   0, 0,+1,   1,0,0,  1,0,
       -1,+1,+1,+1,   0, 0,+1,   1,0,0,  0,1,
       +1,-1,+1,+1,   0, 0,+1,   1,0,0,  1,0,
       -1,-1,+1,+1,   0, 0,+1,   1,0,0,  0,0,
       //  Back
       -1,-1,-1,+1,   0, 0,-1,   0,0,1,  1,0,
       +1,-1,-1,+1,   0, 0,-1,   0,0,1,  0,0,
       -1,+1,-1,+1,   0, 0,-1,   0,0,1,  1,1,
       +1,-1,-1,+1,   0, 0,-1,   0,0,1,  0,0,
       -1,+1,-1,+1,   0, 0,-1,   0,0,1,  1,1,
       +1,+1,-1,+1,   0, 0,-1,   0,0,1,  0,1,
       //  Right
       +1,+1,+1,+1,  +1, 0, 0,   1,1,0,  0,1,
       +1,-1,+1,+1,  +1, 0, 0,   1,1,0,  0,0,
       +1,+1,-1,+1,  +1, 0, 0,   1,1,0,  1,1,
       +1,-1,+1,+1,  +1, 0, 0,   1,1,0,  0,0,
       +1,+1,-1,+1,  +1, 0, 0,   1,1,0,  1,1,
       +1,-1,-1,+1,  +1, 0, 0,   1,1,0,  1,0,
       //  Left
       -1,+1,+1,+1,  -1, 0, 0,   0,1,0,  1,1,
       -1,+1,-1,+1,  -1, 0, 0,   0,1,0,  0,1,
       -1,-1,+1,+1,  -1, 0, 0,   0,1,0,  1,0,
       -1,+1,-1,+1,  -1, 0, 0,   0,1,0,  0,1,
       -1,-1,+1,+1,  -1, 0, 0,   0,1,0,  1,0,
       -1,-1,-1,+1,  -1, 0, 0,   0,1,0,  0,0,
       //  Top
       +1,+1,+1,+1,   0,+1, 0,   0,1,1,  1,0,
       +1,+1,-1,+1,   0,+1, 0,   0,1,1,  1,1,
       -1,+1,+1,+1,   0,+1, 0,   0,1,1,  0,0,
       +1,+1,-1,+1,   0,+1, 0,   0,1,1,  1,1,
       -1,+1,+1,+1,   0,+1, 0,   0,1,1,  0,0,
       -1,+1,-1,+1,   0,+1, 0,   0,1,1,  0,1,
       //  Bottom
       -1,-1,-1,+1,   0,-1, 0,   1,0,1,  0,0,
       +1,-1,-1,+1,   0,-1, 0,   1,0,1,  1,0,
       -1,-1,+1,+1,   0,-1, 0,   1,0,1,  0,1,
       +1,-1,-1,+1,   0,-1, 0,   1,0,1,  1,0,
       -1,-1,+1,+1,   0,-1, 0,   1,0,1,  0,1,
       +1,-1,+1,+1,   0,-1, 0,   1,0,1,  1,1,
       };

    crateTex = new QOpenGLTexture(QImage(":/textures/crate.png").mirrored());
    // Create a vertex array object. In OpenGL ES 2.0 and OpenGL 2.x
    // implementations this is optional and support may not be present
    // at all. Nonetheless the below code works in all cases and makes
    // sure there is a VAO when one is needed.
    m_vao.create();
    QOpenGLVertexArrayObject::Binder vaoBinder(&m_vao);

    // Setup our vertex buffer object.
    m_logoVbo.create();
    m_logoVbo.bind();
    m_logoVbo.allocate(sizeof(cube_data));
    m_logoVbo.write(0,cube_data,sizeof(cube_data));

    // Store the vertex attribute bindings for the program.
    setupVertexAttribs();

    // Our camera never changes in this example.
    m_camera.setToIdentity();
    m_camera.translate(0, 0, -10);

    // Light position is fixed.
    m_program->setUniformValue(m_lightPosLoc, QVector3D(0, 0, 70));

    m_program->release();
}

void oglWidget::setupVertexAttribs()
{
    m_logoVbo.bind();
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    f->glEnableVertexAttribArray(0);
    f->glEnableVertexAttribArray(1);
    f->glEnableVertexAttribArray(2);
    f->glEnableVertexAttribArray(3);
    f->glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 12 * sizeof(GLfloat), 0);
    f->glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 12 * sizeof(GLfloat), reinterpret_cast<void *>(4 * sizeof(GLfloat)));
    f->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 12 * sizeof(GLfloat), reinterpret_cast<void *>(7 * sizeof(GLfloat)));
    f->glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 12 * sizeof(GLfloat), reinterpret_cast<void *>(10 * sizeof(GLfloat)));
    m_logoVbo.release();
}

void oglWidget::paintGL()
{
    //  Wall time (seconds)
    float t = 0.001*time.elapsed();
    zh = fmod(90*t,360);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    m_world.setToIdentity();
    m_world.rotate(180.0f - (m_xRot / 16.0f), 1, 0, 0);
    m_world.rotate(m_yRot / 16.0f, 0, 1, 0);
    m_world.rotate(m_zRot / 16.0f, 0, 0, 1);

    QOpenGLVertexArrayObject::Binder vaoBinder(&m_vao);
    m_program->bind();
    m_program->setUniformValue(m_projMatrixLoc, m_proj);
    m_program->setUniformValue(m_mvMatrixLoc, m_camera * m_world);
    QMatrix3x3 normalMatrix = m_world.normalMatrix();
    m_program->setUniformValue(m_normalMatrixLoc, normalMatrix);
    m_program->setUniformValue(m_vMatrixLoc, m_world);

    crateTex->bind();
    glDrawArrays(GL_TRIANGLES, 0, cube_size);

    m_program->release();
}

void oglWidget::resizeGL(int w, int h)
{
    m_proj.setToIdentity();
    m_proj.perspective(45.0f, GLfloat(w) / h, 0.01f, 100.0f);
}

void oglWidget::mousePressEvent(QMouseEvent *event)
{
    m_lastPos = event->pos();
}

void oglWidget::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - m_lastPos.x();
    int dy = event->y() - m_lastPos.y();

    if (event->buttons() & Qt::LeftButton) {
        setXRotation(m_xRot + 8 * dy);
        setYRotation(m_yRot + 8 * dx);
    } else if (event->buttons() & Qt::RightButton) {
        setXRotation(m_xRot + 8 * dy);
        setZRotation(m_zRot + 8 * dx);
    }
    m_lastPos = event->pos();
}
