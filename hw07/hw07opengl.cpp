//
//  OpenGL widget
//
#include "hw07opengl.h"
#include "Cube.h"
#include "Teapot.h"

//
//  Constructor
//
Hw07opengl::Hw07opengl(QWidget* parent)
: CUgl(parent)
{
   N = 1;
   x0 = y0 = 0;
   zoom = 1;
   Cw = Ch = 0;
   frame = 0;
   framebuf[0] = 0;
   framebuf[1] = 0;
   useCam = 0;
   pixVal = 5;
}

//
//  Reset view
//
void Hw07opengl::reset()
{
   x0 = y0 = 0;
   zoom = 1;
   //  Request redisplay
   update();
}

//
//  Set Camera
//
void Hw07opengl::setCam()
{
   useCam = 1-useCam;
   reinitializeGL();
   //  Request redisplay
   update();
}

//
//  Set Pixelation
//
void Hw07opengl::setPixelation(int pixFact)
{
   pixVal = pixFact;
   update();
}

void Hw07opengl::reinitializeGL()
{
   if (useCam)
   {
      //  Initialize image capture texture
      glGenTextures(1,&frame);
      glBindTexture(GL_TEXTURE_2D,frame);
   }
   else
   {
         // Cube
      Cube* cube = new Cube();
      cube->setScale(0.5,0.5,0.5);
      cube->setTranslate(1,1,0);
      addObject(cube);

   // Teapot
      Teapot* pot = new Teapot(8);
      pot->setScale(0.3);
      pot->setTexture(":/water.png");
      pot->setTranslate(-1,1,0);
      addObject(pot);
   }
}

//
//  Set passes
//
void Hw07opengl::setPasses(int n)
{
   N = n;
   //  Request redisplay
   update();
}

//
//  Set image
//
void Hw07opengl::setImage(QImage img)
{
   //  Copy image to texture
   glBindTexture(GL_TEXTURE_2D,frame);
   QImage rgba = QGLWidget::convertToGLFormat(img);
   Cw = rgba.width();
   Ch = rgba.height();
   glTexImage2D(GL_TEXTURE_2D,0,4,Cw,Ch,0,GL_RGBA,GL_UNSIGNED_BYTE,rgba.bits());
   //  Allocate frame buffer objects to native camera resolution
   if (!framebuf[0] || framebuf[0]->width() != Cw|| framebuf[0]->height() != Ch)
   {
      for (int k=0;k<2;k++)
      {
         //  Allocate frame buffer objects
         if (framebuf[k]) delete framebuf[k];
         framebuf[k] = new QGLFramebufferObject(Cw,Ch);
      }
   }
   //  Request redisplay
   update();
}

//
//  Initialize
//
void Hw07opengl::initializeGL()
{
   //  Load shaders
   addShader("",":/ex12a.frag");
   addShader("",":/ex12b.frag");
   addShader("",":/ex12c.frag");
   addShader("",":/ex12d.frag");
   addShader("",":/ex12e.frag");
   addShader("",":/ex12f.frag");
   addShader("",":/ex12g.frag");
   addShader("",":/ex12h.frag");
   addShader("",":/hw07a.frag");
   addShader("",":/hw07b.frag");
   addShader("",":/hw07c.frag");

   // Cube
   Cube* cube = new Cube();
   cube->setScale(0.5,0.5,0.5);
   cube->setTranslate(1,1,0);
   addObject(cube);

   // Teapot
   Teapot* pot = new Teapot(8);
   pot->setScale(0.3);
   pot->setTexture(":/water.png");
   pot->setTranslate(-1,1,0);
   addObject(pot);

   //  Initialize image capture texture
   //glGenTextures(1,&frame);
   //glBindTexture(GL_TEXTURE_2D,frame);
}


//
//  Set projection when window is resized
//
void Hw07opengl::resizeGL(int width, int height)
{
   doProjection();
   //  Allocate frame buffer objects
   for (int k=0;k<2;k++)
   {
      //  Allocate frame buffer objects
      if (framebuf[k]) delete framebuf[k];
      framebuf[k] = new QGLFramebufferObject(width,height,QGLFramebufferObject::Depth);
   }
   dX = 1.0/width;
   dY = 1.0/height;
}

//
//  Draw the window
//
void Hw07opengl::paintGL()
{
   if (useCam)
   {
   //  Starting texture
      glBindTexture(GL_TEXTURE_2D,frame);
      glEnable(GL_TEXTURE_2D);
   //  Camera aspect ratio
      float Casp = Cw / (float)Ch;

   //  Process
      if (mode)
      {
      //  Viewport is entire image
         glViewport(0,0,Cw,Ch);
      //  Set Projection
         glMatrixMode(GL_PROJECTION);
         glLoadIdentity();
         glOrtho(-Casp, +Casp, -1, +1, -1, +1);
      //  Set ModelView
         glMatrixMode(GL_MODELVIEW);
         glLoadIdentity();

      //  Enable shader
         shader[mode]->bind();

      //  Set shader increments
         shader[mode]->setUniformValue("dX",(float)1.0/Cw);
         shader[mode]->setUniformValue("dY",(float)1.0/Ch);
         shader[mode]->setUniformValue("pix",(float)pixVal);

      //  Ping-Pong at camera resolution
         for (int k=0;k<N;k++)
         {
         //  Pick nearest pixel
            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
         //  Set output buffer
            framebuf[k%2]->bind();
         //  Draw image
            glClear(GL_COLOR_BUFFER_BIT);
            glBegin(GL_QUADS);
            glTexCoord2f(0,0); glVertex2f(-Casp,-1);
            glTexCoord2f(1,0); glVertex2f(+Casp,-1);
            glTexCoord2f(1,1); glVertex2f(+Casp,+1);
            glTexCoord2f(0,1); glVertex2f(-Casp,+1);
            glEnd();
         //  Release output buffer
            framebuf[k%2]->release();
         //  Bind texture to result
            glBindTexture(GL_TEXTURE_2D,framebuf[k%2]->texture());
         }

      //  Release shader
         shader[mode]->release();
      }

   //  Set pixel interpolation
      glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
   //  Window aspect ratio
      float Wasp = width() / (float)height();
   //  Viewport is entire window
      glViewport(0,0,width(),height());
   //  Set Projection
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      glOrtho(-Wasp, +Wasp, -1, +1, -1, +1);
   //  Set ModelView
      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();
      glScaled(zoom,zoom,1);
      glTranslated(x0,y0,0);
   //  Draw to screen
      glClear(GL_COLOR_BUFFER_BIT);
      glBegin(GL_QUADS);
      glTexCoord2f(0,0); glVertex2f(-Casp,-1);
      glTexCoord2f(1,0); glVertex2f(+Casp,-1);
      glTexCoord2f(1,1); glVertex2f(+Casp,+1);
      glTexCoord2f(0,1); glVertex2f(-Casp,+1);
      glEnd();
   //  Done with textures
      glDisable(GL_TEXTURE_2D);
   }
   else
   {

      //  Send output to framebuf[0]
      if (mode) framebuf[0]->bind();

   //  Clear screen and Z-buffer
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      glEnable(GL_DEPTH_TEST);

   //  Set view
      doView();

   //  Applu lighting
      doLight();

   //  Draw scene
      doScene();

   //  Disable lighting and depth
      glDisable(GL_LIGHTING);
      glDisable(GL_DEPTH_TEST);

   //  Apply shader
      if (mode)
      {
      //  Reset projections
         glMatrixMode(GL_PROJECTION);
         glPushMatrix();
         glLoadIdentity();
         glMatrixMode(GL_MODELVIEW);
         glPushMatrix();
         glLoadIdentity();

      //  Enable shader
         shader[mode]->bind();

      //  Set shader increments
         shader[mode]->setUniformValue("dX",dX);
         shader[mode]->setUniformValue("dY",dY);
         shader[mode]->setUniformValue("pix",(float)pixVal);
         

      //  Ping-Pong
         for (int k=0;k<N;k++)
         {
            int last = k%2;
            int next = 1-last;
         //  Set output to next framebuffer except for the last pass
            if (k+1<N)
               framebuf[next]->bind();
            else
               framebuf[last]->release();
         //  Get the texture
            glBindTexture(GL_TEXTURE_2D,framebuf[last]->texture());
         //  Exercise shader
            glClear(GL_COLOR_BUFFER_BIT);
            glBegin(GL_QUADS);
            glTexCoord2f(0,0); glVertex2f(-1,-1);
            glTexCoord2f(1,0); glVertex2f(+1,-1);
            glTexCoord2f(1,1); glVertex2f(+1,+1);
            glTexCoord2f(0,1); glVertex2f(-1,+1);
            glEnd();
         }

      //  Release shader
         shader[mode]->release();
      }

   //  Undo transformations
      glPopMatrix();
      glMatrixMode(GL_PROJECTION);
      glPopMatrix();
      glMatrixMode(GL_MODELVIEW);
   }
}

/******************************************************************/
/*************************  Mouse Events  *************************/
/******************************************************************/
//
//  Mouse moved
//

void Hw07opengl::mouseMoveEvent(QMouseEvent* e)
{
   if (mouse)
   {
      QPoint d = e->pos()-pos;      //  Change in mouse location
      if (useCam)
      {
         x0 += d.x()/(zoom*width());   //  Translate x movement to azimuth
         y0 -= d.y()/(zoom*height());  //  Translate y movement to elevation
      }
      else
      {
         th = (th+d.x())%360;      //  Translate x movement to azimuth
         ph = (ph+d.y())%360;      //  Translate y movement to elevation
      }
      pos = e->pos();               //  Remember new location
      update();                   //  Request redisplay
   }
}

//
//  Mouse wheel
//
void Hw07opengl::wheelEvent(QWheelEvent* e)
{
   //  Zoom out
   if (e->delta()<0)
   {
      if (useCam) 
         zoom *= 1.05;
      else 
         dim += 0.1;
   }
   //  Zoom in
   else if (zoom>1)
   {
      if (useCam) 
         zoom /= 1.05;
      else 
         dim -= 0.1;
   }
   //  Request redisplay
   if (!useCam)  doProjection();
   update();
}

