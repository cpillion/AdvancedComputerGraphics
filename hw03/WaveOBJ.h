//
//  Wave OBJ class
//  The constructor places the object at the origin
//  All parameters are assigned default values
//
#ifndef WAVEOBJ_H
#define WAVEOBJ_H

#include "Object.h"
#include <QString>
#include <QHash>

//  Material structure
typedef struct
{
   Color Ke,Ka,Kd,Ks; //  Colors
   float Ns;          //  Shininess
   float d;           //  Transparency
   unsigned int map;  //  Texture
} Material;

class WaveOBJ: public Object
{
private:
   float sr;              // Scale
   int   list;            // Display list
   QHash<QString,Material> mat;
   void SetMaterial(const QString& name);
   void LoadMaterial(const QString& name,const QString& path="");
public:
   WaveOBJ(const QString& file,const QString& path,const float size=1,const Color rgb=Color(1,1,1));  //  Constructor
   void setScale(float s);    //  Set scale
   void display();            //  Render the object
};

#endif
