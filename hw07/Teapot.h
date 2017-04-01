//
//  Teapot class
//  The constructor sets the position, size and rotation
//  All parameters are assigned default values
//
#ifndef TEAPOT_H
#define TEAPOT_H

#include "Object.h"

class Teapot: public Object
{
private:
   int   n;  //  Number of patches
   float sr; // Scale
public:
   Teapot(int patches,const QString tex="",const float size=1.0,const Color col=Color(1,1,1));   //  Constructor
   void setScale(float r) ;  //  Set scale
   void display();           //  Render the teapot
};

#endif
