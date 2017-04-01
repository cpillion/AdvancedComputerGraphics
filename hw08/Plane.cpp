//
//  Plane class
//
#include "Plane.h"
#include <math.h>


//
//  Constructor
//
Plane::Plane(int N,const QString tex,const float size,const Color col)
{
   inc = (N>0) ? N : 1;
   if (tex.length()>0) setTexture(tex);
   setScale(size);
   setColor(col);
}

//
//  Set size
//
void Plane::setScale(float r)
{
   sr = r;
}


//
//  Display the sphere
//
void Plane::display()
{
   if (!show) return;
    //  Draw Plane
    
    //  Save transformation
    glPushMatrix();
    //  Offset, scale, rotate and color
    useTransform(1, 1, 0.0);
    useColor();
    EnableTex();
    glBegin(GL_QUADS);
    glVertex3f( 1.0,  1.0, 0.0);
    glTexCoord2f(1.0, 1.0);
    glNormal3f(0.0, 0.0, 1.0);
    glVertex3f( 1.0, -1.0, 0.0);
    glTexCoord2f(1.0, 0.0);
    glNormal3f(0.0, 0.0, 1.0);
    glVertex3f(-1.0, -1.0, 0.0);
    glTexCoord2f(0.0, 0.0);
    glNormal3f(0.0, 0.0, 1.0);
    glVertex3f(-1.0,  1.0, 0.0);
    glTexCoord2f(0.0, 1.0);
    glNormal3f(0.0, 0.0, 1.0);
    glEnd();
    DisableTex();
    //  Undo transofrmations
    glPopMatrix();
}
