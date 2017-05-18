//
//  Application Window Widget
//

#include <QComboBox>
#include <QLabel>
#include <QGridLayout>
#include <QPushButton>
#include "appWindow.h"

//
//  Constructor
//
appWindow::appWindow()
{
   //  Set window title
   setWindowTitle(tr("Final Project: Terrain Rendering in OpenGL4 and Qt5 (by Chris Pillion)"));

   //  Create new OpenGL widget
   ogl = new oglWidget;

   //  Select shader
   QComboBox* shader = new QComboBox();
   shader->addItem("Wire Frame");
   shader->addItem("Height Gradient");
   shader->addItem("Textures");
   shader->addItem("Phong Lighting");
   shader->addItem("Textures and Lighting");
   shader->setCurrentIndex(1);

   //  Select projection
   QComboBox* projection = new QComboBox();
   projection->addItem("Orthogonal (for Debugging)");
   projection->addItem("Perspective");
   projection->setCurrentIndex(1);

   //  View angle and zoom
   QLabel* angles = new QLabel();

   //  Map Size Slider
   QSlider* slider = new QSlider(Qt::Horizontal);
   slider->setRange(10,1000);

   //  Peak Size Slider
   QSlider* slider2 = new QSlider(Qt::Horizontal);
   slider2->setRange(0,60);

   //  Light Angle Slider
   QSlider* zhSlide = new QSlider(Qt::Horizontal);
   zhSlide->setRange(0,360);

   // Animate the scene option
   light = new QPushButton("Pause");

   //  Reset
   QPushButton* rst = new QPushButton("Reset");
   //  Quit
   QPushButton* quit = new QPushButton("Quit");

   //  Set layout of child widgets
   QGridLayout* layout = new QGridLayout;
   layout->addWidget(ogl,0,0,9,1);
   layout->addWidget(new QLabel("Shader"),0,1);
   layout->addWidget(shader,0,2);
   layout->addWidget(new QLabel("Projection"),1,1);
   layout->addWidget(projection,1,2);
   layout->addWidget(new QLabel("Angles"),2,1);
   layout->addWidget(angles,2,2);
   layout->addWidget(new QLabel("Map Size"),3,1);
   layout->addWidget(slider,3,2);
   layout->addWidget(new QLabel("Peak Size"),4,1);
   layout->addWidget(slider2,4,2);
   layout->addWidget(new QLabel("Light Angle"),5,1);
   layout->addWidget(zhSlide,5,2);
   layout->addWidget(new QLabel("Animation"),6,1);
   layout->addWidget(light,6,2);
   layout->addWidget(rst,8,1);
   layout->addWidget(quit,8,2);
   //  Manage resizing
   layout->setColumnStretch(0,100);
   layout->setColumnMinimumWidth(0,100);
   layout->setRowStretch(7,100);
   setLayout(layout);

   //  Connect valueChanged() signals to ogl
   connect(shader,SIGNAL(currentIndexChanged(int)), ogl,SLOT(setMode(int)));
   connect(projection,SIGNAL(currentIndexChanged(int)) , ogl,SLOT(setPerspective(int)));
   //  Connect angles() and zoom() signal to labels
   connect(ogl,SIGNAL(angles(QString)) , angles,SLOT(setText(QString)));
   //  Connect reset() signal
   connect(slider,SIGNAL(valueChanged(int)) , ogl,SLOT(setMsize(int)));
   connect(slider2,SIGNAL(valueChanged(int)) , ogl,SLOT(setHsize(int)));
   connect(zhSlide,SIGNAL(valueChanged(int)) , ogl, SLOT(setLightAngle(int)));
   connect(light,SIGNAL(pressed()),this,SLOT(lmove()));
   connect(rst  ,SIGNAL(pressed()),ogl,SLOT(reset()));
   //  Connect quit() signal to qApp::quit()
   connect(quit,SIGNAL(pressed()) , qApp,SLOT(quit()));
}

//
//  Light pause/move
//
void appWindow::lmove()
{
   bool pause = (light->text()=="Pause");
   if (pause)
      light->setText("Animate");
   else
      light->setText("Pause");
   ogl->setLightMove(!pause);
}
