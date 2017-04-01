#ifndef HW08V_H
#define HW08V_H

#include <QWidget>
#include <QSlider>
#include <QDoubleSpinBox>
#include "hw08opengl.h"

class Hw08viewer : public QWidget
{
Q_OBJECT
private:
   QSlider*     Msize;
   QSlider*     Hsize;
   Hw08opengl*  ogl;
public:
    Hw08viewer();
};

#endif
