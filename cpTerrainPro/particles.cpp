#include "particles.h"


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

particles::particles()
{
    N = 30;
    Vert  = new float[3*N*N];
    Color = new float[3*N*N];
    Vel   = new float[3*N*N];
    Start = new float[N*N];
    InitPart();
}


/*
 *  Initialize particles
 */
void particles::InitPart(void)
{
   //  Array Pointers
   float* vert  = Vert;
   float* color = Color;
   float* vel   = Vel;
   float* start = Start;
   //  Loop over NxN patch
   int n = N;
   int dim = 10;
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
void particles::DrawPart(void)
{
   QOpenGLFunctions glf(QOpenGLContext::currentContext());
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
      glEnable(GL_POINT_SPRITE);
      glTexEnvi(GL_POINT_SPRITE,GL_COORD_REPLACE,GL_TRUE);
      glEnable(GL_BLEND);
      glBlendFunc(GL_SRC_ALPHA,GL_ONE);
      glDepthMask(0);
      //  Draw arrays
      glDrawArrays(GL_POINTS,0,N*N);
      glDisable(GL_POINT_SPRITE);
      glDisable(GL_BLEND);
      glDepthMask(1);

   //  Disable arrays
   glDisableClientState(GL_VERTEX_ARRAY);
   glDisableClientState(GL_COLOR_ARRAY);
   glf.glDisableVertexAttribArray(VELOCITY_ARRAY);
   glf.glDisableVertexAttribArray(START_ARRAY);
}
