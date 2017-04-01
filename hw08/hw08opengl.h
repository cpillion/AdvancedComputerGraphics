//
//  OpenGL Hw08opengl Widget
//

#ifndef HW08OPENGL_H
#define HW08OPENGL_H

#include "CUgl.h"
#define MAP_X  256                   // size of map along x-axis
#define MAP_Z  256                   // size of map along z-axis

class Hw08opengl : public CUgl
{
Q_OBJECT
private:
   int     mode;  //  Mode
   float   MAP_SCALE; 
   float   H_SCALE; 
   unsigned char* hMap; //  Image Data 
   float terrain[MAP_X][MAP_Z][3];
   unsigned int snow, rock, mud, grass, alpha, norm;
public:
   Hw08opengl(QWidget* parent=0);                  //  Constructor
   QSize sizeHint() const {return QSize(400,400);} //  Default size of widget
   unsigned int InitializeTerrain();
   void DrawTerrain();
public slots:
    void setMode(int m);                   //  Slot mode
    void setMsize(int pct);                  //  Slot to set position
    void setHsize(int pct); 
protected:
    void initializeGL();                   //  Initialize widget
    void paintGL();                        //  Draw widget
};

#endif
