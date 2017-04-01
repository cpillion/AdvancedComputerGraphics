//
//  OpenGL Hw07opengl Widget
//

#ifndef HW07OPENGL_H
#define HW07OPENGL_H

#include "CUgl.h"
#include <QImage>

class Hw07opengl : public CUgl
{
Q_OBJECT
private:
   int     N;            //  Number of passes
   float   x0,y0;        //  Image center
   float   zoom;         //  Zoom
   int     Cw,Ch;        //  Camera image size
   float   dX,dY;        //  Increment
   unsigned int frame;                //  Image frame
   QGLFramebufferObject* framebuf[2]; //  Framebuffers
   int     useCam;
   int     pixVal;
public:
   Hw07opengl(QWidget* parent=0);                  //  Constructor
   QSize sizeHint() const {return QSize(400,400);} //  Default size of widget
public slots:
   void setPasses(int pass);              //  Slot to set number of passes
   void setImage(QImage img);             //  Slot to set image
   void reset();                          //  Reset view
   void setCam();
   void setPixelation(int pixFact);
protected:
   void initializeGL();                   //  Initialize widget
   void reinitializeGL();
   void paintGL();                        //  Draw widget
   void resizeGL(int,int);                //  Resize widget
   void mouseMoveEvent(QMouseEvent*);     //  Mouse moved
   void wheelEvent(QWheelEvent*);         //  Mouse wheel
};

#endif
