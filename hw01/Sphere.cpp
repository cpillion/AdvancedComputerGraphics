//
//  Sphere class
//
#include "Sphere.h"
#include <math.h>
#define Cos(th) cos(M_PI/180*(th))
#define Sin(th) sin(M_PI/180*(th))

//
//  Constructor
//
Sphere::Sphere(int n)
{
   sr = 1;
   inc = (n>0) ? n : 1;
}

//
//  Set radius
//
void Sphere::scale(float r)
{
   sr = r;
}

//
//  Draw vertex in polar coordinates with normal
//
static void Vertex(float th,float ph)
{
   float s = th/360;
   float t = ph/180+0.5;
   float x = Cos(th)*Cos(ph);
   float y = Sin(th)*Cos(ph);
   float z =         Sin(ph);
   //  For a sphere at the origin, the position
   //  and normal vectors are the same
   glTexCoord2f(s,t);
   glNormal3f(x,y,z);
   glVertex3f(x,y,z);
}

//
//  Display the sphere
//
void Sphere::display()
{
   //  Save transformation
   glPushMatrix();
   //  Offset, scale, rotate and color
   useTransform(sr,sr,sr);
   useColor();
   EnableTex();
   //  Bands of latitude
   float dh = 90.0/inc;
   for (int i=-inc;i<inc;i++)
   {
      float ph = i*dh;
      glBegin(GL_QUAD_STRIP);
      for (int j=0;j<=inc;j++)
      {
         float th = ph*dh;
         Vertex(th,ph);
         Vertex(th,ph+dh);
      }
      glEnd();
   }
   DisableTex();
   //  Undo transofrmations
   glPopMatrix();
}
