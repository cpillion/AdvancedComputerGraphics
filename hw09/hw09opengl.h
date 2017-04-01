//
//  OpenGL Hw09opengl Widget
//

#ifndef HW09OPENGL_H
#define HW09OPENGL_H

#include "CUgl.h"

class Hw09opengl : public CUgl
{
Q_OBJECT
private:

   int     N;         //  Particle count
   float   zh;        //  Light position
   int     n;         //  Particle count
   float*  Vert;      //  Vertices
   float*  Color;     //  Colors
   float*  Vel;       //  Velocities
   float*  Start;     //  Start time
   int wind;          //  X Wind Speed
   int fall;          //  Snowfall Speed
public:
   Hw09opengl(QWidget* parent=0);                  //  Constructor
   QSize sizeHint() const {return QSize(400,400);} //  Default size of widget
public slots:
   void setMode(int m);  //  Setmode
   void setWind(int wi); //  Set Wind Speed
   void setFall(int vy); //  Set Snowfall Speed
protected:
   void initializeGL();  //  Initialize widget
   void paintGL();       //  Draw widget
private:
  void InitPart();
  void DrawPart();
};

#endif
