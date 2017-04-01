#ifndef HW03V_H
#define HW03V_H

#include <QWidget>
#include <QSlider>
#include <QDoubleSpinBox>
#include "hw03opengl.h"

class Hw03viewer : public QWidget
{
Q_OBJECT
private:
   QSlider*     Lpos;
   QSlider*     Zpos;
   QPushButton* light;
   Hw03opengl*  ogl;
private slots:
   void lmove();        //  Light movement
public:
    Hw03viewer();
};

#endif
