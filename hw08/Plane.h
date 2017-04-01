//
//  Plane class
//  The constructor sets the position, size and color
//  All parameters are assigned default values
//
#ifndef PLANE_H
#define PLANE_H

#include "Object.h"

class Plane: public Object
{
private:
   int   inc;  //  Increment
   float sr;   // Size
public:
   Plane(int patches,const QString tex="",const float size=1.0,const Color col=Color(1,1,1));       //  Constuctor
   void setScale(float r); //  Set radius
   void display();           //  Render the sphere
};

#endif
