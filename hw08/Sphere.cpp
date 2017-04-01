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
Sphere::Sphere(int N,const QString tex,const float size,const Color col)
{
   inc = (N>0) ? N : 1;
   if (tex.length()>0) setTexture(tex);
   setScale(size);
   setColor(col);
}

//
//  Set radius
//
void Sphere::setScale(float r)
{
   sr = r;
}

//
//  Draw vertex in polar coordinates with normal
//new Sphere(8,"",2)
static void Vertex(float th,float ph)
{
   float s = th/360;
   float t = ph/180+0.5;
   float x = Sin(th)*Cos(ph);
   float y =         Sin(ph);
   float z = Cos(th)*Cos(ph);
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
   if (!show) return;
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
      for (int j=-2*inc;j<=2*inc;j++)
      {
         float th = j*dh;
         Vertex(th,ph);
         Vertex(th,ph+dh);
      }
      glEnd();
   }
   DisableTex();
   //  Undo transofrmations
   glPopMatrix();
}
