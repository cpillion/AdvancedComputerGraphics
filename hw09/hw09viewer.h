#ifndef HW09V_H
#define HW09V_H

#include <QWidget>
#include <QSlider>
#include <QDoubleSpinBox>
#include "hw09opengl.h"

class Hw09viewer : public QWidget
{
Q_OBJECT
private:
   Hw09opengl*  ogl;
public:
    Hw09viewer();
};

#endif
