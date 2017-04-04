//
//  CU OpenGL Widget
//
#include "CUgl.h"
#define Cos(th) cos(M_PI/180*(th))
#define Sin(th) sin(M_PI/180*(th))
#include <iostream>

//
//  Constructor
//
CUgl::CUgl(QWidget* parent)
    : QOpenGLWidget(parent)
{
   //  Initial shader
   mode  = 0;
   shader.append(NULL);
   //  Draw all objects
   obj = -1;
   //  Projection
   mouse = false;
   asp = 1;
   Dim = dim = 6;
   fov = 0;
   th = -45;
   ph = 15;
   //  Light settings
   La = 0.3;
   Ld = 1.0;
   Ls = 1.0;
   //  Light position
   Lr = 6;
   zh = 0;
   ylight = 2;
   //  Light animation
   move = true;
   //  100 fps timer connected to tick()
   timer.setInterval(10);
   connect(&timer,SIGNAL(timeout()),this,SLOT(tick()));
   timer.start();
   //  Elapsed time timer
   time.start();
}

//
// Set max frame rate
//
void CUgl::maxFPS(bool on)
{
   timer.setInterval(on?0:10);
}


//
//  Timer tick
//
void CUgl::tick()
{
   if (move)
   {
      zh = timer.interval() ? zh+0.2*timer.interval() : fmod(0.090*time.elapsed(),360);
      if (zh>360) zh -= 360;
      update();
   }
}

//
//  Reset view
//
void CUgl::reset()
{
   th = ph = 0;
   dim = Dim;
   doProjection();
   //  Request redisplay
   update();
}

//
//  Set domain size
//
void CUgl::setDim(float d)
{
   Dim = dim = d;
   //  Request redisplay
   update();
}

//
//  Set shader
//
void CUgl::setShader(int sel)
{
   if (sel>=0 && sel<shader.length())
      mode = sel;
   //  Request redisplay
   update();
}

//
//  Set object
//
void CUgl::setObject(int type)
{
   if (type>=0 && type<objects.size())
      obj = type;
   //  Request redisplay
   update();
}

//
//  Add object
//
void CUgl::addObject(Object* obj)
{
   objects.append(obj);
}

//
//  Draw scene
//
void CUgl::doScene()
{
   //  Draw single object
   if (obj>=0 && obj<objects.length())
      objects[obj]->display();
   //  Draw all objects
   else
      for (int k=0;k<objects.length();k++)
         objects[k]->display();
         
}

//
//  Set projection
//
void CUgl::setPerspective(int on)
{
   fov = on ? 40 : 0;
   doProjection();
   //  Request redisplay
   update();
}

//
//  Set view
//
QMatrix4x4 CUgl::doView()
{
   QMatrix4x4 view;
   if (fov) view.translate(0,0,-2*dim);
   view.rotate(ph, 1, 0, 0);
   view.rotate(th, 0, 1, 0);
   //  Emit angles to display
   emit angles(QString::number(th)+","+QString::number(ph));
   return view;
}

//
//  Light animation
//
void CUgl::setLightMove(bool on)
{
   move = on;
   update();
}

//
//  Draw vertex in polar coordinates
//
static void Vertex(double th,double ph)
{
   glVertex3d(Sin(th)*Cos(ph),Cos(th)*Cos(ph),Sin(ph));
}

//
//  Draw a ball at (x,y,z) radius r
//
static void ball(double x,double y,double z,double r)
{
   QMatrix4x4 ballMat;
   ballMat.setToIdentity();
   //  Offset, scale and rotate
   ballMat.translate(x, y, z);
   ballMat.scale(r,r,r);
}

//
//  Set light intensity
//
void CUgl::setLightElevation(int per)
{
   ylight = 0.01*per*Lr;
   update();
}

//
//  Set light intensity
//
void CUgl::setLightAngle(int th)
{
   zh = th;
   update();
}

//
//  Set light intensity
//
void CUgl::setLightIntensity(float a,float d,float s)
{
   La = a;
   Ld = d;
   Ls = s;
   update();
}

//
//  Apply light
//
QVector4D CUgl::doLight()
{
   //  Light position
   float x = Lr*Cos(zh);
   float y = ylight;
   float z = Lr*Sin(zh);
   QVector4D Position = QVector4D(x,y,z,1.0);
   //ball(x,y,z,.5);
   return Position;
}

//
//  Initialize
//
void CUgl::initializeGL()
{
}

//
//  Set projection when window is resized
//
void CUgl::resizeGL(int,int)
{
   doProjection();
}

//
//  Throw a fatal error and die
//
void CUgl::Fatal(QString message)
{
   QMessageBox::critical(this,"CUgl",message);
   QApplication::quit();
}

//
//  Set OpenGL projection
//
void CUgl::doProjection()
{
   //  Window aspect ration
   asp = width() / (float)height();
   //  Viewport is whole screen
   glViewport(0,0,width(),height());
   //  Set Projection
   proj.setToIdentity();
   if (fov)
      proj.perspective(fov,asp,dim/4,4*dim);
   else
      proj.ortho(-dim*asp, +dim*asp, -dim, +dim, -dim, +dim);
}

/******************************************************************/
/*************************  Mouse Events  *************************/
/******************************************************************/
//
//  Mouse pressed
//
void CUgl::mousePressEvent(QMouseEvent* e)
{
   mouse = true;
   pos = e->pos();  //  Remember mouse location
}

//
//  Mouse released
//
void CUgl::mouseReleaseEvent(QMouseEvent*)
{
    mouse = false;
}

//
//  Mouse moved
//
void CUgl::mouseMoveEvent(QMouseEvent* e)
{
   if (mouse)
   {
      QPoint d = e->pos()-pos;  //  Change in mouse location
      th = (th+d.x())%360;      //  Translate x movement to azimuth
      ph = (ph+d.y())%360;      //  Translate y movement to elevation
      pos = e->pos();           //  Remember new location
      update();                 //  Request redisplay
   }
}

//
//  Mouse wheel
//
void CUgl::wheelEvent(QWheelEvent* e)
{
   //  Zoom out
   if (e->delta()<0)
      dim += 0.1;
   //  Zoom in
   else if (dim>1)
      dim -= 0.1;
   //  Request redisplay
   doProjection();
   update();
}

//
//  Load shader
//
void CUgl::addShader(QString vert,QString frag,QString names)
{
   QStringList name = names.split(',');
   QOpenGLFunctions glf(QOpenGLContext::currentContext());
   QOpenGLShaderProgram* prog = new QOpenGLShaderProgram;
   //  Vertex shader
   if (vert.length() && !prog->addShaderFromSourceFile(QOpenGLShader::Vertex,vert))
      Fatal("Error compiling "+vert+"\n"+prog->log());
   //  Fragment shader
   if (frag.length() && !prog->addShaderFromSourceFile(QOpenGLShader::Fragment,frag))
      Fatal("Error compiling "+frag+"\n"+prog->log());
   //  Bind Attribute Locations
   for (int k=0;k<name.size();k++)
      if (name[k].length())
         glf.glBindAttribLocation(prog->programId(),k,name[k].toLatin1().data());
   //  Link
   if (!prog->link())
      Fatal("Error linking shader\n"+prog->log());
   //  Push onto stack
   else
      shader.append(prog);
}

//
//  Load shader
//
void CUgl::addShader3(QString vert,QString geom,QString frag)
{
   QOpenGLShaderProgram* prog = new QOpenGLShaderProgram;
   //  Vertex shader
   if (vert.length() && !prog->addShaderFromSourceFile(QOpenGLShader::Vertex,vert))
      Fatal("Error compiling "+vert+"\n"+prog->log());
   //  Fragment shader
   if (geom.length() && !prog->addShaderFromSourceFile(QOpenGLShader::Geometry,geom))
      Fatal("Error compiling "+geom+"\n"+prog->log());
   //  Fragment shader
   if (frag.length() && !prog->addShaderFromSourceFile(QOpenGLShader::Fragment,frag))
      Fatal("Error compiling "+frag+"\n"+prog->log());
   //  Link
   if (!prog->link())
      Fatal("Error linking shader\n"+prog->log());
   //  Push onto stack
   else
      shader.append(prog);
}

//
//  Load image to texture unit
//
//unsigned int CUgl::loadImage(const QString file)
//{
//   //  Load image
//   QImage img(file);
//   //  Bind texture
//   unsigned int tex;
//   glGenTextures(1,&tex);
//   glBindTexture(GL_TEXTURE_2D,tex);
//   //  Copy image to texture
//   QImage rgba = QOpenGLWidget::convertToGLFormat(img);
//   glTexImage2D(GL_TEXTURE_2D,0,4,rgba.width(),rgba.height(),0,GL_RGBA,GL_UNSIGNED_BYTE,rgba.bits());
//   //  Set pixel interpolation
//   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
//   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
//   return tex;
//}
