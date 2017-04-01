//
//  OpenGL widget
//
#include "hw03opengl.h"
#include "Cube.h"
#include "WaveOBJ.h"
#include "Teapot.h"
#include <OpenGL/gl.h>

//
//  Constructor
//
Hw03opengl::Hw03opengl(QWidget* parent)
    : CUgl(parent)
{
   t0 = frame = 0;
}

//
//  Initialize
//
void Hw03opengl::initializeGL()
{
   //  Load shaders
   addShader("",":/ex04a.frag");
   addShader(":/ex04b.vert",":/ex04b.frag");
   addShader(":/ex04c.vert",":/ex04c.frag");
   addShader(":/ex04d.vert",":/ex04d.frag");
   addShader(":/ex04e.vert",":/ex04e.frag");
   addShader(":/hw03a.vert",":/hw03a.frag");
   

   //  Load objects
   addObject(new Cube(":/crate.png"));
   addObject(new Teapot(8,":/pi.png",0.5));
   addObject(new WaveOBJ("cruiser.obj",":/"));
   setObject(0);

   //  Set max frame rate
   maxFPS(1);
}

//
//  Draw the window
//
void Hw03opengl::paintGL()
{
   //  Clear screen and Z-buffer
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   //  Enable Z-buffering
   if (dMode==0 || dMode==2)
      glEnable(GL_DEPTH_TEST);
   else
      glDisable(GL_DEPTH_TEST);
   //  Enable face culling
   if (dMode!=0) 
      glEnable(GL_CULL_FACE);
   else
      glDisable(GL_CULL_FACE);


   //  Set view
   doView();

   //  Apply lighting
   doLight();

   //  Apply shader
   if (mode)
   {
      shader[mode]->bind();
      //  Dimensions
      QVector3D loc(0,0,1);
      shader[mode]->setUniformValue("loc",loc);
      //  Time
      float t = getTime();
      shader[mode]->setUniformValue("time",t);
   }

   //  Draw scene
   doScene();

   //  Release shader
   if (mode) shader[mode]->release();
   glDisable(GL_LIGHTING);
   glDisable(GL_DEPTH_TEST);

   //  Frame counter
   frame++;
   int t = time.elapsed()/1000;
   if (t>t0)
   {
      emit fps(QString::number(frame));
      t0 = t;
      frame = 0;
   }
}
