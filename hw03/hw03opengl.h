//
//  OpenGL Hw03opengl Widget
//

#ifndef HW03OPENGL_H
#define HW03OPENGL_H

#include "CUgl.h"

class Hw03opengl : public CUgl
{
Q_OBJECT
private:
   int frame; //  Frame counter
   int t0;    //  Frame seconds
public:
   Hw03opengl(QWidget* parent=0);                   // Constructor
   QSize sizeHint() const {return QSize(400,400);}  // Default size of widget
protected:
    void initializeGL();  // Initialize widget
    void paintGL();       // Draw widget
signals:
    void fps(QString);    // Frames per second
};

#endif
