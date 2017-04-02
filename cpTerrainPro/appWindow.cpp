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
   setWindowTitle(tr("Hw08: Textures for Data Storage (by Chris Pillion)"));

   //  Create new OpenGL widget
   ogl = new oglWidget;

   //  Select shader
   QComboBox* shader = new QComboBox();
   shader->addItem("Shader Off");
   shader->addItem("Shader On");

   //  View angle and zoom
   QLabel* angles = new QLabel();

   //  Slider
   QSlider* slider = new QSlider(Qt::Horizontal);
   slider->setRange(1,50);

   //  Slider
   QSlider* slider2 = new QSlider(Qt::Horizontal);
   slider2->setRange(0,20);

   //  Reset
   QPushButton* rst = new QPushButton("Reset");
   //  Quit
   QPushButton* quit = new QPushButton("Quit");

   //  Set layout of child widgets
   QGridLayout* layout = new QGridLayout;
   layout->addWidget(ogl,0,0,6,1);
   layout->addWidget(new QLabel("Shader"),0,1);
   layout->addWidget(shader,0,2);
   layout->addWidget(new QLabel("Angles"),1,1);
   layout->addWidget(angles,1,2);
   layout->addWidget(new QLabel("Map Size"),2,1);
   layout->addWidget(slider,2,2);
   layout->addWidget(new QLabel("Peak Size"),3,1);
   layout->addWidget(slider2,3,2);
   layout->addWidget(rst,5,1);
   layout->addWidget(quit,5,2);
   //  Manage resizing
   layout->setColumnStretch(0,100);
   layout->setColumnMinimumWidth(0,100);
   layout->setRowStretch(4,100);
   setLayout(layout);

   //  Connect valueChanged() signals to ogl
   connect(shader,SIGNAL(currentIndexChanged(int)), ogl,SLOT(setMode(int)));
   //  Connect angles() and zoom() signal to labels
   connect(ogl,SIGNAL(angles(QString)) , angles,SLOT(setText(QString)));
   //  Connect reset() signal
   connect(slider,SIGNAL(valueChanged(int)) , ogl,SLOT(setMsize(int)));
   connect(slider2,SIGNAL(valueChanged(int)) , ogl,SLOT(setHsize(int)));
   connect(rst  ,SIGNAL(pressed()),ogl,SLOT(reset()));
   //  Connect quit() signal to qApp::quit()
   connect(quit,SIGNAL(pressed()) , qApp,SLOT(quit()));
}
