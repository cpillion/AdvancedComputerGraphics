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
   Dim = dim = 4;
   fov = 0;
   th = ph = 45;
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
   th = ph = 45;
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
   //  glColor sets ambient and diffuse color materials
   glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
   glEnable(GL_COLOR_MATERIAL);

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
      dim += 10;
   //  Zoom in
   else if (dim>1)
      dim -= 10;
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

unsigned char* CUgl::LoadTexBMP(const char* file)
{
    FILE*          f;          // File pointer
    unsigned short magic;      // Image magic
    unsigned int   dx,dy,size; // Image dimensions
    unsigned short nbp,bpp;    // Planes and bits per pixel
    unsigned char* image;      // Image data
    unsigned int   k;          // Counter
    int            max;        // Maximum texture dimensions
    
    //  Open file
    f = fopen(file,"rb");
    if (!f) Fatal("Cannot open file %s\n",file);
    //  Check image magic
    if (fread(&magic,2,1,f)!=1) Fatal("Cannot read magic from %s\n",file);
    if (magic!=0x4D42 && magic!=0x424D) Fatal("Image magic not BMP in %s\n",file);
    //  Seek to and read header
    if (fseek(f,16,SEEK_CUR) || fread(&dx ,4,1,f)!=1 || fread(&dy ,4,1,f)!=1 ||
        fread(&nbp,2,1,f)!=1 || fread(&bpp,2,1,f)!=1 || fread(&k,4,1,f)!=1)
        Fatal("Cannot read header from %s\n",file);
    //  Reverse bytes on big endian hardware (detected by backwards magic)
    if (magic==0x424D)
    {
        Reverse(&dx,4);
        Reverse(&dy,4);
        Reverse(&nbp,2);
        Reverse(&bpp,2);
        Reverse(&k,4);
    }
    //  Check image parameters
    glGetIntegerv(GL_MAX_TEXTURE_SIZE,&max);
    if (dx<1 || dx>max) Fatal("%s image width %d out of range 1-%d\n",file,dx,max);
    if (dy<1 || dy>max) Fatal("%s image height %d out of range 1-%d\n",file,dy,max);
    if (nbp!=1)  Fatal("%s bit planes is not 1: %d\n",file,nbp);
    if (bpp!=24) Fatal("%s bits per pixel is not 24: %d\n",file,bpp);
    if (k!=0)    Fatal("%s compressed files not supported\n",file);
#ifndef GL_VERSION_2_0
    //  OpenGL 2.0 lifts the restriction that texture size must be a power of two
    for (k=1;k<dx;k*=2);
    if (k!=dx) Fatal("%s image width not a power of two: %d\n",file,dx);
    for (k=1;k<dy;k*=2);
    if (k!=dy) Fatal("%s image height not a power of two: %d\n",file,dy);
#endif
    
    //  Allocate image memory
    size = 3*dx*dy;
    image = (unsigned char*) malloc(size);
    if (!image) Fatal("Cannot allocate %d bytes of memory for image %s\n",size,file);
    //  Seek to and read image
    if (fseek(f,20,SEEK_CUR) || fread(image,size,1,f)!=1) Fatal("Error reading data from image %s\n",file);
    fclose(f);
    //  Reverse colors (BGR -> RGB)
    for (k=0;k<size;k+=3)
    {
        unsigned char temp = image[k];
        image[k]   = image[k+2];
        image[k+2] = temp;
    }
    
    return image;

 }


/*
 *  Reverse n bytes
 */
void CUgl::Reverse(void* x,const int n)
{
    int k;
    char* ch = (char*)x;
    for (k=0;k<n/2;k++)
    {
        char tmp = ch[k];
        ch[k] = ch[n-1-k];
        ch[n-1-k] = tmp;
    }
}


void CUgl::Fatal(const char* format , ...)
{
    va_list args;
    va_start(args,format);
    vfprintf(stderr,format,args);
    va_end(args);
    exit(1);
}