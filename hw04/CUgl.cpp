//
//  CU OpenGL Widget
//
//#define GL_GLEXT_PROTOTYPES
#include "CUgl.h"
#include <math.h>
#define Cos(th) cos(M_PI/180*(th))
#define Sin(th) sin(M_PI/180*(th))

//
//  Constructor
//
CUgl::CUgl(QWidget* parent,bool fixed)
    : QGLWidget(parent)
{
   //  Initial shader
   mode  = 0;
   //  Fixed pipeline
   if (fixed) shader.push_back(NULL);
   //  Draw all objects
   obj = -1;
   //  Projection
   mouse = false;
   asp = 1;
   dim = 4;
   fov = 0;
   th = ph = 0;
   //  Light settings
   La = 0.3;
   Ld = 1.0;
   Ls = 1.0;
   //  Light position
   Lr = 2;
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
   dim = 3;
   doProjection();
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
   objects.push_back(obj);
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
   fov = on ? 55 : 0;
   doProjection();
   //  Request redisplay
   update();
}

//
//  Set view
//
void CUgl::doView()
{
   glLoadIdentity();
   if (fov) glTranslated(0,0,-2*dim);
   glRotated(ph,1,0,0);
   glRotated(th,0,1,0);
   //  Emit angles to display
   emit angles(QString::number(th)+","+QString::number(ph));
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
   //  Save transformation
   glPushMatrix();
   //  Offset, scale and rotate
   glTranslated(x,y,z);
   glScaled(r,r,r);
   //  Bands of latitude
   for (int ph=-90;ph<90;ph+=10)
   {
      glBegin(GL_QUAD_STRIP);
      for (int th=0;th<=360;th+=20)
      {
         Vertex(th,ph);
         Vertex(th,ph+10);
      }
      glEnd();
   }
   //  Undo transofrmations
   glPopMatrix();
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
QVector3D CUgl::doLight()
{
   //  Light position
   float x = Lr*Cos(zh);
   float y = ylight;
   float z = Lr*Sin(zh);
   float Position[] = {x,y,z,1.0};

   //  Draw light position (no lighting yet)
   glColor3f(1,1,1);
   ball(x,y,z,0.1);

   //  OpenGL should normalize normal vectors
   glEnable(GL_NORMALIZE);
   //  Enable lighting
   glEnable(GL_LIGHTING);
   //  Enable light 0
   glEnable(GL_LIGHT0);

   //  Set ambient, diffuse, specular components and position of light 0
   float Ambient[]  = {La,La,La,1.0};
   float Diffuse[]  = {Ld,Ld,Ld,1.0};
   float Specular[] = {Ls,Ls,Ls,1.0};
   glLightfv(GL_LIGHT0,GL_AMBIENT ,Ambient);
   glLightfv(GL_LIGHT0,GL_DIFFUSE ,Diffuse);
   glLightfv(GL_LIGHT0,GL_SPECULAR,Specular);
   glLightfv(GL_LIGHT0,GL_POSITION,Position);

   //  Light angle
   emit light(int(zh));

   return QVector3D(x,y,z);
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
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   if (fov)
   {
      double zmin = dim/16;
      double zmax = 16*dim;
      double ydim = zmin*tan(fov*M_PI/360);
      double xdim = ydim*asp;
      glFrustum(-xdim,+xdim,-ydim,+ydim,zmin,zmax);
   }
   else
      glOrtho(-dim*asp, +dim*asp, -dim, +dim, -dim, +dim);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
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
void CUgl::addShader(QString vert,QString frag)
{
   QGLShaderProgram* prog = new QGLShaderProgram;
   //  Vertex shader
   if (vert.length() && !prog->addShaderFromSourceFile(QGLShader::Vertex,vert))
      Fatal("Error compiling "+vert+"\n"+prog->log());
   //  Fragment shader
   if (frag.length() && !prog->addShaderFromSourceFile(QGLShader::Fragment,frag))
      Fatal("Error compiling "+frag+"\n"+prog->log());
   //  Link
   if (!prog->link())
      Fatal("Error linking shader\n"+prog->log());
   //  Push onto stack
   else
      shader.push_back(prog);
}


//
//  Load image to texture unit
//
unsigned int CUgl::loadImage(const QString file)
{
   //  Load image
   QImage img(file);
   //  Bind texture
   unsigned int tex;
   glGenTextures(1,&tex);
   glBindTexture(GL_TEXTURE_2D,tex);
   //  Copy image to texture
   QImage rgba = QGLWidget::convertToGLFormat(img);
   glTexImage2D(GL_TEXTURE_2D,0,4,rgba.width(),rgba.height(),0,GL_RGBA,GL_UNSIGNED_BYTE,rgba.bits());
   //  Set pixel interpolation
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
   return tex;
}
