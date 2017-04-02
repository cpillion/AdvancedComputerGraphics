#ifndef APPWIN_H
#define APPWIN_H

#include <QWidget>
#include <QSlider>
#include <QDoubleSpinBox>
#include "oglWidget.h"

class appWindow : public QWidget
{
Q_OBJECT
private:
   QSlider*     Msize;
   QSlider*     Hsize;
   oglWidget*  ogl;
public:
    appWindow();
};

#endif
