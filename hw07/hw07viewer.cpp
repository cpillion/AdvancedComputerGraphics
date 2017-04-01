//
//  Hw07viewer Widget
//

#include <QComboBox>
#include <QLabel>
#include <QGridLayout>
#include "hw07viewer.h"
#include "hw07frame.h"

//
//  Constructor
//
Hw07viewer::Hw07viewer()
{
   //  Set window title
   setWindowTitle(tr("Hw07:  Image Processing (by Chris Pillion)"));

   //  Create new OpenGL widget
   ogl = new Hw07opengl;

   camera = new QCamera;
   Hw07frame* frame = new Hw07frame;
   camera->setCaptureMode(QCamera::CaptureStillImage);
   camera->setViewfinder(frame);
   connect(frame,SIGNAL(frameAvailable(QImage)), ogl,SLOT(setImage(QImage)));

   //  Select shader
   QComboBox* shader = new QComboBox();
   shader->addItem("None");
   shader->addItem("Copy");
   shader->addItem("Sharpen");
   shader->addItem("Blur");
   shader->addItem("Erosion");
   shader->addItem("Dilation");
   shader->addItem("Laplacian");
   shader->addItem("Prewitt");
   shader->addItem("Sobel");
   shader->addItem("Cartoon (HW07)");
   shader->addItem("Faded (HW07)");
   shader->addItem("Pixelation (HW07)");

   //  Select number of passes
   QSpinBox* passes = new QSpinBox();
   passes->setRange(1,20);

   //  Select projection
   projection = new QComboBox();
   pLabel = new QLabel("Projection");
   projection->addItem("Orthogonal");
   projection->addItem("Perspective");
   projection->setCurrentIndex(1);

   //  Center position
   Lpos = new QSlider(Qt::Horizontal);
   lpLabel = new QLabel("Light Position");
   Zpos = new QSlider(Qt::Horizontal);
   zpLabel = new QLabel("Light Elevation");
   Lpos->setRange(0,360);
   Zpos->setRange(-100,100);

   //  View angle and zoom
   angles = new QLabel();

   //  Pause/resume button
   light = new QPushButton("Pause");
   lLabel = new QLabel("Light");

   aLabel = new QLabel("Angles");

   // Camera Mode
   cam = new QPushButton("Camera On");

   // Control Pixelation
   pixFact = new QSlider(Qt::Horizontal);
   pixLabel = new QLabel("Pixelation Factor");
   pixFact->setRange(5,20);
   pixFact->hide();
   pixLabel->hide();

   //  Reset
   QPushButton* rst = new QPushButton("Reset");
   //  Quit
   QPushButton* quit = new QPushButton("Quit");

   //  Set layout of child widgets
   QGridLayout* layout = new QGridLayout;
   layout->addWidget(ogl,0,0,10,1);
   layout->addWidget(new QLabel("Shader"),0,1);
   layout->addWidget(shader,0,2);
   layout->addWidget(new QLabel("Passes"),1,1);
   layout->addWidget(passes,1,2);
   layout->addWidget(pLabel,2,1);
   layout->addWidget(projection,2,2);
   layout->addWidget(lpLabel,3,1);
   layout->addWidget(Lpos,3,2);
   layout->addWidget(zpLabel,4,1);
   layout->addWidget(Zpos,4,2);
   layout->addWidget(lLabel,5,1);
   layout->addWidget(light,5,2);
   layout->addWidget(aLabel,6,1);
   layout->addWidget(angles,6,2);
   layout->addWidget(pixLabel,7,1);
   layout->addWidget(pixFact,7,2);
   layout->addWidget(new QLabel("Camera"),8,1);
   layout->addWidget(cam,8,2);
   layout->addWidget(rst,9,1);
   layout->addWidget(quit,9,2);
   //  Manage resizing
   layout->setColumnStretch(0,100);
   layout->setColumnMinimumWidth(0,100);
   layout->setRowStretch(7,100);
   setLayout(layout);

   //  Connect valueChanged() signals to ogl
   connect(shader,SIGNAL(currentIndexChanged(int))    , ogl,SLOT(setShader(int)));
   connect(passes,SIGNAL(valueChanged(int))           , ogl,SLOT(setPasses(int)));
   connect(projection,SIGNAL(currentIndexChanged(int)), ogl,SLOT(setPerspective(int)));
   connect(Lpos,SIGNAL(valueChanged(int)) , ogl,SLOT(setLightAngle(int)));
   connect(Zpos,SIGNAL(valueChanged(int)) , ogl,SLOT(setLightElevation(int)));
   //  Connect angles() and zoom() signal to labels
   connect(ogl,SIGNAL(angles(QString)) , angles,SLOT(setText(QString)));
   connect(ogl,SIGNAL(light(int))      , Lpos,SLOT(setValue(int)));
   //  Connect reset() and lmove() signals
   connect(rst  ,SIGNAL(pressed()),ogl,SLOT(reset()));
   connect(light,SIGNAL(pressed()),this,SLOT(lmove()));
   // Pixelation
   connect(pixFact, SIGNAL(valueChanged(int)), ogl, SLOT(setPixelation(int))); 
   connect(shader,SIGNAL(currentIndexChanged(int))    , this,SLOT(setPix(int)));   
   //  Camera signal
   connect(cam  ,SIGNAL(pressed()),ogl,SLOT(setCam()));
   connect(cam  ,SIGNAL(pressed()),this,SLOT(setViewCam()));  
   //  Connect quit() signal to qApp::quit()
   connect(quit,SIGNAL(pressed()) , qApp,SLOT(quit()));

   //  Light elevation
   Zpos->setValue(100);
}


//
//  Light pause/move
//
void Hw07viewer::lmove()
{
   bool pause = (light->text()=="Pause");
   if (pause)
      light->setText("Animate");
   else
      light->setText("Pause");
   ogl->setLightMove(!pause);
}

void Hw07viewer::setViewCam()
{
   bool camOn = (cam->text()=="Camera On");
   if (camOn)
   {
      cam->setText("Camera Off");
      projection->hide();
      pLabel->hide();
      Lpos->hide();
      lpLabel->hide();
      Zpos->hide();
      zpLabel->hide();
      light->hide();
      lLabel->hide();
      angles->hide();
      aLabel->hide();
      //  Create new camera and frame widgets
      camera->start();
   }
   else
   {
      cam->setText("Camera On");
      projection->show();
      pLabel->show();
      Lpos->show();
      lpLabel->show();
      Zpos->show();
      zpLabel->show();
      light->show();
      lLabel->show();
      camera->stop();
   }
}

void Hw07viewer::setPix(int mode)
{
   if (mode == 11)
   {
      pixFact->show();
      pixLabel->show();
   }
   else
   {
      pixFact->hide();
      pixLabel->hide();
   }
}

