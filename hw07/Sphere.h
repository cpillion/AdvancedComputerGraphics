//
//  Sphere class
//  The constructor sets the position, radius and color
//  All parameters are assigned default values
//
#ifndef SPHERE_H
#define SPHERE_H

#include "Object.h"

class Sphere: public Object
{
private:
   int   inc;  //  Increment
   float sr;   //  Radius
public:
   Sphere(int n);       //  Constuctor
   void scale(float r); //  Set radius
   void display();      //  Render the sphere
};

#endif
