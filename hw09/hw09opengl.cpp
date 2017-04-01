//
//  OpenGL widget
//
#include "hw09opengl.h"
#include <QGLFunctions>
#include <QStringList>
#include "Noise.h"
#include <math.h>
#include <iostream>

//  Set up array indexes for program
const int VELOCITY_ARRAY=4;
const int START_ARRAY=5;
const char* Name = ",,,,Vel,Start";

/*
 *  Random numbers with range and offset
 */
static float frand(float rng,float off)
{
   return rand()*rng/RAND_MAX+off;
}

/*
 *  Initialize particles
 */
void Hw09opengl::InitPart(void)
{
   //  Array Pointers
   float* vert  = Vert;
   float* color = Color;
   float* vel   = Vel;
   float* start = Start;
   //  Loop over NxN patch
   n = N;
   for (int i=0;i<n;i++)
      for (int j=0;j<n;j++)
      {
         //  Location x,y,z
         //  Spread snowfall out over twice the viewing plane
         *vert++ = frand(2*dim, -dim);
         *vert++ = dim;
         *vert++ = frand(2*dim, -dim);
         //  Color r,g,b (0.5-1.0)
         *color++ = frand(0.5,0.5);
         *color++ = frand(0.5,0.5);
         *color++ = frand(0.5,0.5);
         //  Velocity
         *vel++ = frand( 0.0,0.0);
         *vel++ = frand( 0.0,0.0);
         *vel++ = frand( 0.0,0.0);
         //  Launch time
         *start++ = frand(2*dim,0.0);
      }
}

/*
 *  Draw particles
 */
void Hw09opengl::DrawPart(void)
{
   QGLFunctions glf(QGLContext::currentContext());
   //  Set particle size
   glPointSize(9);
   //  Point vertex location to local array Vert
   glVertexPointer(3,GL_FLOAT,0,Vert);
   //  Point color array to local array Color
   glColorPointer(3,GL_FLOAT,0,Color);
   //  Point attribute arrays to local arrays
   glf.glVertexAttribPointer(VELOCITY_ARRAY,3,GL_FLOAT,GL_FALSE,0,Vel);
   glf.glVertexAttribPointer(START_ARRAY,1,GL_FLOAT,GL_FALSE,0,Start);
   //  Enable arrays used by DrawArrays
   glEnableClientState(GL_VERTEX_ARRAY);
   glEnableClientState(GL_COLOR_ARRAY);
   glf.glEnableVertexAttribArray(VELOCITY_ARRAY);
   glf.glEnableVertexAttribArray(START_ARRAY);
   //  Set transparent large particles
   if (mode)
   {
      glEnable(GL_POINT_SPRITE);
      glTexEnvi(GL_POINT_SPRITE,GL_COORD_REPLACE,GL_TRUE);
      glEnable(GL_BLEND);
      glBlendFunc(GL_SRC_ALPHA,GL_ONE);
      glDepthMask(0);
      //  Draw arrays
      glDrawArrays(GL_POINTS,0,n*n);
      glDisable(GL_POINT_SPRITE);
      glDisable(GL_BLEND);
      glDepthMask(1);
   }
   //  Disable arrays
   glDisableClientState(GL_VERTEX_ARRAY);
   glDisableClientState(GL_COLOR_ARRAY);
   glf.glDisableVertexAttribArray(VELOCITY_ARRAY);
   glf.glDisableVertexAttribArray(START_ARRAY);
}

//
//  Constructor
//
Hw09opengl::Hw09opengl(QWidget* parent)
    : CUgl(parent,false)
{
   N = 50;
   wind = 0;
   fall = 25;
   Vert  = new float[3*N*N];
   Color = new float[3*N*N];
   Vel   = new float[3*N*N];
   Start = new float[N*N];
   InitPart();
}

//
//  Initialize
//
void Hw09opengl::setMode(int m)
{
   setShader(m);
   InitPart();
}

void Hw09opengl::setWind(int wi)
{
   wind = wi;
}

void Hw09opengl::setFall(int vy)
{
   fall = vy;
}

//
//  Initialize
//
void Hw09opengl::initializeGL()
{
   setPerspective(0);
   QGLFunctions glf(QGLContext::currentContext());
   //  Load shaders
   addShader(":/hw09.vert","",Name);
   addShader(":/hw09b.vert",":/hw09.frag",Name);

   //  Load random texture
   CreateNoise3D(GL_TEXTURE1);

   //  Load snow particle
   QPixmap snow(":/snowflake.png");
   bindTexture(snow,GL_TEXTURE_2D);
}

//
//  Draw the window
//
void Hw09opengl::paintGL()
{
   //  Wall time (seconds)
   float t = 0.001*time.elapsed();
   zh = fmod(90*t,360);

   //  Clear screen and Z-buffer
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glEnable(GL_DEPTH_TEST);

   //  Set view
   doView();

   //  Apply shader
   shader[mode]->bind();
   shader[mode]->setUniformValue("time",t);
   shader[mode]->setUniformValue("dim",dim);
   shader[mode]->setUniformValue("wind", (float)wind/50);
   shader[mode]->setUniformValue("fall", (float)fall/10);
   shader[mode]->setUniformValue("img",0);
   shader[mode]->setUniformValue("Noise3D",1);

   //  Draw scene
   if (mode) DrawPart();

   //  Release shader
   shader[mode]->release();

   //  Draw axes
   glBegin(GL_LINES);
   glColor3d(1, 1, 1);
   glVertex3d(0,0,0);
   glVertex3d(1,0,0);
   glVertex3d(0,0,0);
   glVertex3d(0,1,0);
   glVertex3d(0,0,0);
   glVertex3d(0,0,1);
   glEnd();

   //  Label axes
   renderText(1,0,0,"X");
   renderText(0,1,0,"Y");
   renderText(0,0,1,"Z");
}
