//
//  Hw09viewer Widget
//

#include <QComboBox>
#include <QLabel>
#include <QGridLayout>
#include "hw09viewer.h"

//
//  Constructor
//
Hw09viewer::Hw09viewer()
{
   //  Set window title
   setWindowTitle(tr("HW09: Advanced Shaders (by Chris Pillion)"));

   //  Create new OpenGL widget
   ogl = new Hw09opengl;

   //  Select shader
   QComboBox* shader = new QComboBox();
   shader->addItem("No Precipitation");
   shader->addItem("Snow");

   //  Select projection
   QComboBox* projection = new QComboBox();
   projection->addItem("Perspective");
   projection->addItem("Orthogonal");

   //  Slider
   QSlider* slider = new QSlider(Qt::Horizontal);
   slider->setRange(0,50);

   //  Slider
   QSlider* slider2 = new QSlider(Qt::Horizontal);
   slider2->setRange(1,50);

   //  View angle and zoom
   QLabel* angles = new QLabel();

   //  Reset
   QPushButton* rst = new QPushButton("Reset");
   //  Quit
   QPushButton* quit = new QPushButton("Quit");

   //  Set layout of child widgets
   QGridLayout* layout = new QGridLayout;
   layout->addWidget(ogl,0,0,7,1);
   layout->addWidget(new QLabel("Shader"),0,1);
   layout->addWidget(shader,0,2);
   layout->addWidget(new QLabel("Projection"),1,1);
   layout->addWidget(projection,1,2);
   layout->addWidget(new QLabel("Wind Effect"),2,1);
   layout->addWidget(slider,2,2);
   layout->addWidget(new QLabel("Fall Speed"),3,1);
   layout->addWidget(slider2,3,2);
   layout->addWidget(new QLabel("Angles"),4,1);
   layout->addWidget(angles,4,2);
   layout->addWidget(rst,6,1);
   layout->addWidget(quit,6,2);
   //  Manage resizing
   layout->setColumnStretch(0,100);
   layout->setColumnMinimumWidth(0,100);
   layout->setRowStretch(5,100);
   setLayout(layout);

   //  Connect valueChanged() signals to ogl
   connect(shader,SIGNAL(currentIndexChanged(int))     , ogl,SLOT(setMode(int)));
   connect(projection,SIGNAL(currentIndexChanged(int)) , ogl,SLOT(setPerspective(int)));
   connect(slider,SIGNAL(valueChanged(int)) , ogl,SLOT(setWind(int)));
   connect(slider2,SIGNAL(valueChanged(int)) , ogl,SLOT(setFall(int)));

   //  Connect angles() and zoom() signal to labels
   connect(ogl,SIGNAL(angles(QString)) , angles,SLOT(setText(QString)));
   //  Connect reset() and lmove() signals
   connect(rst  ,SIGNAL(pressed()),ogl,SLOT(reset()));
   //  Connect quit() signal to qApp::quit()
   connect(quit,SIGNAL(pressed()) , qApp,SLOT(quit()));
}
