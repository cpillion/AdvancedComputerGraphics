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
   mode  = 1;
   shader.append(NULL);
   //  Draw all objects
   obj = -1;
   //  Projection
   mouse = false;
   asp = 1;
   Dim = dim = 30;
   fov = 40;
   th = -130;
   ph = -5;
   x = -3;
   z = -16;
   y = 10;
   //  Light settings
   La = 0.3;
   Ld = 1.0;
   Ls = 1.0;
   //  Light position
   Lr = 40;
   zh = 0;
   ylight = 10;
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
//   if (fov) view.translate(0,0,-2*dim);
//   view.rotate(ph, 1, 0, 0);
//   view.rotate(th, 0, 1, 0);
   view.lookAt(QVector3D(x, y, z),
               QVector3D(x+Sin(th), y+Sin(ph), z-Cos(th)),
               QVector3D(0, 1, 0));
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

////
////  Draw vertex in polar coordinates
////
//static void Vertex(double th,double ph)
//{
//   glVertex3d(Sin(th)*Cos(ph),Cos(th)*Cos(ph),Sin(ph));
//}

//
////  Draw a ball at (x,y,z) radius r
////
//static void ball(double x,double y,double z,double r)
//{
//   QMatrix4x4 ballMat;
//   ballMat.setToIdentity();
//   //  Offset, scale and rotate
//   ballMat.translate(x, y, z);
//   ballMat.scale(r,r,r);
//}

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
   // Update the viewport matrix
   float w2 = width() / 2.0f;
   float h2 = height() / 2.0f;
   viewPortMat.setToIdentity();
   viewPortMat.setColumn( 0, QVector4D( w2, 0.0f, 0.0f, 0.0f ) );
   viewPortMat.setColumn( 1, QVector4D( 0.0f, h2, 0.0f, 0.0f ) );
   viewPortMat.setColumn( 2, QVector4D( 0.0f, 0.0f, 1.0f, 0.0f ) );
   viewPortMat.setColumn( 3, QVector4D( w2, h2, 0.0f, 1.0f ) );
   //  Set Projection
   proj.setToIdentity();
   if (fov)
   {
      proj.perspective(fov,asp,dim/32,32*dim);
   }
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
      dim += 0.5;
   //  Zoom in
   else if (dim>1)
      dim -= 0.5;
   //  Request redisplay
   doProjection();
   update();
}


void CUgl::keyPressEvent( QKeyEvent* e )
{
    switch ( e->key() )
    {
    case Qt::Key_W:
        x += Sin(th);
        y += Sin(ph);
        z -= Cos(th);
        break;
    case Qt::Key_S:
        x -= Sin(th);
        y -= Sin(ph);
        z += Cos(th);
        break;
    default:
        std::cout << "Invalid Key Pressed" << std::endl;
    }
    std::cout << "X: " << x << " Z: " << z << std::endl;
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

void CUgl::addShaderTess(QString vert,QString tcs, QString tes, QString geom, QString frag, QString names)
{
    QStringList name = names.split(',');
    QOpenGLFunctions glf(QOpenGLContext::currentContext());
    QOpenGLShaderProgram* prog = new QOpenGLShaderProgram;
    //  Vertex shader
    if (vert.length() && !prog->addShaderFromSourceFile(QOpenGLShader::Vertex,vert))
       Fatal("Error compiling "+vert+"\n"+prog->log());
    //  Tessellation Control shader
    if (tcs.length() && !prog->addShaderFromSourceFile(QOpenGLShader::TessellationControl,tcs))
       Fatal("Error compiling "+tcs+"\n"+prog->log());
    //  Tessellation Eval shader
    if (tes.length() && !prog->addShaderFromSourceFile(QOpenGLShader::TessellationEvaluation,tes))
       Fatal("Error compiling "+tes+"\n"+prog->log());
    //  Geometry shader
    if (geom.length() && !prog->addShaderFromSourceFile(QOpenGLShader::Geometry,geom))
       Fatal("Error compiling "+geom+"\n"+prog->log());
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
    if (!f) Fatal("Cannot open file");
    //  Check image magic
    if (fread(&magic,2,1,f)!=1) Fatal("Cannot read magic");
    if (magic!=0x4D42 && magic!=0x424D) Fatal("Image magic not BMP");
    //  Seek to and read header
    if (fseek(f,16,SEEK_CUR) || fread(&dx ,4,1,f)!=1 || fread(&dy ,4,1,f)!=1 ||
        fread(&nbp,2,1,f)!=1 || fread(&bpp,2,1,f)!=1 || fread(&k,4,1,f)!=1)
        Fatal("Cannot read header");
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
//    if (dx<1 || dx>max) Fatal(file+" image width "+dx+" out of range 1-"+max);
//    if (dy<1 || dy>max) Fatal(file+" image height "+dy+" out of range 1-"+max);
//    if (nbp!=1)  Fatal(file+" bit planes is not 1: "+nbp);
//    if (bpp!=24) Fatal(file+" bits per pixel is not 24: "+bpp);
//    if (k!=0)    Fatal(file+" compressed files not supported");
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
//    if (!image) Fatal("Cannot allocate %d bytes of memory for image %s\n",size,file);
    //  Seek to and read image
    if (fseek(f,20,SEEK_CUR) || fread(image,size,1,f)!=1) Fatal("Error reading data from image");
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


