#ifndef HW07V_H
#define HW07V_H

#include <QWidget>
#include <QSlider>
#include <QDoubleSpinBox>
#include <QCamera>
#include "hw07opengl.h"

class Hw07viewer : public QWidget
{
Q_OBJECT
private:
   QCamera* camera;
   QSlider*     Lpos;
   QSlider*     Zpos;
   QSlider*     pixFact;
   QPushButton* light;
   QPushButton* cam;
   QComboBox*   projection;
   QLabel* pLabel;
   QLabel* lpLabel;
   QLabel* zpLabel;
   QLabel* lLabel;
   QLabel* angles;
   QLabel* aLabel;
   QLabel* pixLabel;
   QString* anglesWidget;
   Hw07opengl*  ogl;
private slots:
   void lmove();        //  Light movement
   void setViewCam();
   void setPix(int);
public:
    Hw07viewer();
};

#endif
