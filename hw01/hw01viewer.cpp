//
//  Ex01viewer Widget
//

#include <QComboBox>
#include <QLabel>
#include <QGridLayout>
#include <QInputDialog>
#include "hw01viewer.h"
#include "hw01opengl.h"

//
//  Constructor
//
Hw01viewer::Hw01viewer()
{
   //  Set window title
   setWindowTitle(tr("Homework 01: NDC to RGB Shader (by Chris Pillion)"));

   //  Create new OpenGL widget
   Hw01opengl* ogl = new Hw01opengl;

   //  Select shader
   QComboBox* shader = new QComboBox();
   shader->addItem("None");
   shader->addItem("Basic");

   //  Select projection
   QComboBox* projection = new QComboBox();
   projection->addItem("Orthogonal");
   projection->addItem("Perspective");

   //  Select object
   QComboBox* object = new QComboBox();
   object->addItem("Cube");
   object->addItem("Teapot");
   object->addItem("Suzanne");
    
   // Control Movement on Screen
   QComboBox* moveControl = new QComboBox();
   moveControl->addItem("User Controlled");
   moveControl->addItem("Box Bounce");

   // User Controlled Position
   QSlider* Xpos = new QSlider(Qt::Horizontal);
   QSlider* Ypos = new QSlider(Qt::Horizontal);
   QSlider* Zpos = new QSlider(Qt::Horizontal);
   Xpos->setRange(-100,100);
   Ypos->setRange(-100,100);
   Zpos->setRange(-100,100);
    
    
   //  Lighting
   QCheckBox* lighting = new QCheckBox("");

   //  View angle
   QLabel* angles = new QLabel();

   //  View angle
   QLabel* center = new QLabel();
    
   //  Quit
   QPushButton* quit = new QPushButton("Quit");

   //  Set layout of child widgets
   QGridLayout* layout = new QGridLayout;
   layout->addWidget(ogl,0,0,12,1);
   layout->addWidget(new QLabel("Shader"),0,1);
   layout->addWidget(shader,0,2);
   layout->addWidget(new QLabel("Projection"),1,1);
   layout->addWidget(projection,1,2);
   layout->addWidget(new QLabel("Object"),2,1);
   layout->addWidget(object,2,2);
   layout->addWidget(new QLabel("Lighting"),3,1);
   layout->addWidget(lighting,3,2);
   layout->addWidget(new QLabel("Movement"),4,1);
   layout->addWidget(moveControl, 4,2);
   layout->addWidget(new QLabel("X Position"),5,1);
   layout->addWidget(Xpos,5,2);
   layout->addWidget(new QLabel("Y Position"),6,1);
   layout->addWidget(Ypos,6,2);
   layout->addWidget(new QLabel("Z Position"),7,1);
   layout->addWidget(Zpos,7,2);
   layout->addWidget(new QLabel("Angles"),8,1);
   layout->addWidget(angles,8,2);
   layout->addWidget(new QLabel("NDC Postition"),9,1);
   layout->addWidget(center,9,2);
   layout->addWidget(quit,11,2);
   //  Manage resizing
   layout->setColumnStretch(0,100);
   layout->setColumnMinimumWidth(0,100);
    layout->setColumnMinimumWidth(2, 175);
   layout->setRowStretch(10,100);
   setLayout(layout);

   //  Connect valueChanged() signals to ogl
   connect(shader,SIGNAL(currentIndexChanged(int))     , ogl,SLOT(setShader(int)));
   connect(object,SIGNAL(currentIndexChanged(int))     , ogl,SLOT(setObject(int)));
   connect(projection,SIGNAL(currentIndexChanged(int)) , ogl,SLOT(setPerspective(int)));
   connect(lighting,SIGNAL(stateChanged(int))          , ogl,SLOT(setLighting(int)));
   connect(moveControl,SIGNAL(currentIndexChanged(int)), ogl,SLOT(setMove(int)));
   connect(Xpos,SIGNAL(valueChanged(int))              , ogl,SLOT(setX(int)));
   connect(Ypos,SIGNAL(valueChanged(int))              , ogl,SLOT(setY(int)));
   connect(Zpos,SIGNAL(valueChanged(int))              , ogl,SLOT(setZ(int)));
   //  Connect angles() and center() signal to labels
   connect(ogl,SIGNAL(angles(QString)) , angles,SLOT(setText(QString)));
   connect(ogl,SIGNAL(center(QString)) , center,SLOT(setText(QString)));
   //  Connect quit() signal to qApp::quit()
   connect(quit,SIGNAL(pressed()) , qApp,SLOT(quit()));
}
