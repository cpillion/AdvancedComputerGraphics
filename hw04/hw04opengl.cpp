//
//  OpenGL widget
//
#include "hw04opengl.h"

//
//  Constructor
//
Hw04opengl::Hw04opengl(QWidget* parent)
    : CUgl(parent)
{
}

//
//  Cube Vertexes
//
const int cube_size=36;
const float cube_data[] =  // Vertex data
{
//  X  Y  Z  W   Nx Ny Nz    R G B   s t
   //  Front
   +1,+1,+1,+1,   0, 0,+1,   1,0,0,  1,1,
   -1,+1,+1,+1,   0, 0,+1,   1,0,0,  0,1,
   +1,-1,+1,+1,   0, 0,+1,   1,0,0,  1,0,
   -1,+1,+1,+1,   0, 0,+1,   1,0,0,  0,1,
   +1,-1,+1,+1,   0, 0,+1,   1,0,0,  1,0,
   -1,-1,+1,+1,   0, 0,+1,   1,0,0,  0,0,
   //  Back
   -1,-1,-1,+1,   0, 0,-1,   0,0,1,  1,0,
   +1,-1,-1,+1,   0, 0,-1,   0,0,1,  0,0,
   -1,+1,-1,+1,   0, 0,-1,   0,0,1,  1,1,
   +1,-1,-1,+1,   0, 0,-1,   0,0,1,  0,0,
   -1,+1,-1,+1,   0, 0,-1,   0,0,1,  1,1,
   +1,+1,-1,+1,   0, 0,-1,   0,0,1,  0,1,
   //  Right
   +1,+1,+1,+1,  +1, 0, 0,   1,1,0,  0,1,
   +1,-1,+1,+1,  +1, 0, 0,   1,1,0,  0,0,
   +1,+1,-1,+1,  +1, 0, 0,   1,1,0,  1,1,
   +1,-1,+1,+1,  +1, 0, 0,   1,1,0,  0,0,
   +1,+1,-1,+1,  +1, 0, 0,   1,1,0,  1,1,
   +1,-1,-1,+1,  +1, 0, 0,   1,1,0,  1,0,
   //  Left
   -1,+1,+1,+1,  -1, 0, 0,   0,1,0,  1,1,
   -1,+1,-1,+1,  -1, 0, 0,   0,1,0,  0,1,
   -1,-1,+1,+1,  -1, 0, 0,   0,1,0,  1,0,
   -1,+1,-1,+1,  -1, 0, 0,   0,1,0,  0,1,
   -1,-1,+1,+1,  -1, 0, 0,   0,1,0,  1,0,
   -1,-1,-1,+1,  -1, 0, 0,   0,1,0,  0,0,
   //  Top
   +1,+1,+1,+1,   0,+1, 0,   0,1,1,  1,0,
   +1,+1,-1,+1,   0,+1, 0,   0,1,1,  1,1,
   -1,+1,+1,+1,   0,+1, 0,   0,1,1,  0,0,
   +1,+1,-1,+1,   0,+1, 0,   0,1,1,  1,1,
   -1,+1,+1,+1,   0,+1, 0,   0,1,1,  0,0,
   -1,+1,-1,+1,   0,+1, 0,   0,1,1,  0,1,
   //  Bottom
   -1,-1,-1,+1,   0,-1, 0,   1,0,1,  0,0,
   +1,-1,-1,+1,   0,-1, 0,   1,0,1,  1,0,
   -1,-1,+1,+1,   0,-1, 0,   1,0,1,  0,1,
   +1,-1,-1,+1,   0,-1, 0,   1,0,1,  1,0,
   -1,-1,+1,+1,   0,-1, 0,   1,0,1,  0,1,
   +1,-1,+1,+1,   0,-1, 0,   1,0,1,  1,1,
   };

//
//  Initialize
//
void Hw04opengl::initializeGL()
{
   // Texture
   QPixmap crate(":/crate.png");
   tex = bindTexture(crate,GL_TEXTURE_2D);

   //  Load shaders
   addShader(":/hw04.vert",":/hw04.frag");

   //  Cube vertex buffer object
   //  Copy data to vertex buffer object
   cube_buffer.create();
   cube_buffer.bind();
   cube_buffer.setUsagePattern(QGLBuffer::StaticDraw);
   cube_buffer.allocate(sizeof(cube_data));
   cube_buffer.write(0,cube_data,sizeof(cube_data));
   //  Unbind this buffer
   cube_buffer.release();
}

//
//  Draw the window
//
void Hw04opengl::paintGL()
{
   //  Clear screen and Z-buffer
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glEnable(GL_DEPTH_TEST);

   //  Set projection
   doProjection();
   //  Set view
   doView();
   //  Set light - will generate warning since lpos is not used (yet)
   QVector3D lpos = doLight();

   //  Fixed pipeline
   if (mode==0)
   {
      //  Enable textures
      glEnable(GL_TEXTURE_2D);
      glBindTexture(GL_TEXTURE_2D,tex);

      //  Enabe arrays
      glEnableClientState(GL_VERTEX_ARRAY);
      glEnableClientState(GL_NORMAL_ARRAY);
      glEnableClientState(GL_COLOR_ARRAY);
      glEnableClientState(GL_TEXTURE_COORD_ARRAY);

      //  Set pointers
      
      glVertexPointer  (4,GL_FLOAT,12*sizeof(GLfloat),cube_data);
      glNormalPointer  (  GL_FLOAT,12*sizeof(GLfloat),cube_data+4);
      glColorPointer   (3,GL_FLOAT,12*sizeof(GLfloat),cube_data+7);
      glTexCoordPointer(2,GL_FLOAT,12*sizeof(GLfloat),cube_data+10);

      //  Draw the cube
      glDrawArrays(GL_TRIANGLES,0,cube_size);

      //  Disable arrays
      glDisableClientState(GL_VERTEX_ARRAY);
      glDisableClientState(GL_NORMAL_ARRAY);
      glDisableClientState(GL_COLOR_ARRAY);
      glDisableClientState(GL_TEXTURE_COORD_ARRAY);

      //  Disable textures and lighting
      glDisable(GL_TEXTURE_2D);
      glDisable(GL_LIGHTING);
   }
   //  OpenGL 4 style shaders
   else
   {
      //  Create the View matrix
      QMatrix4x4 view;
      if (fov) view.translate(0,0,-2*dim);
      view.rotate(ph,1,0,0);
      view.rotate(th,0,1,0);

      // Create the ModelView Matrix
      QMatrix4x4 mv = view;

      // Enable shader
      shader[mode]->bind();
      //  Set Modelview and Projection Matrix
      shader[mode]->setUniformValue("ProjectionMatrix",proj);
      shader[mode]->setUniformValue("ViewMatrix", view);
      shader[mode]->setUniformValue("ModelViewMatrix",mv);
      shader[mode]->setUniformValue("NormalMatrix", mv.normalMatrix()); // Thanks Mat4x4!

      // Light Properties
      shader[mode]->setUniformValue("Ambient", QVector3D(0.3, 0.3, 0.3));
      shader[mode]->setUniformValue("Diffuse", QVector3D(1.0, 1.0, 1.0));
      shader[mode]->setUniformValue("Specular", QVector3D(1.0, 1.0, 1.0));
      shader[mode]->setUniformValue("Position", QVector4D(lpos.x(),lpos.y(),lpos.z(), 1.0));


      //  Select cube buffer
      cube_buffer.bind();
      //   Attribute 0: vertex coordinate (vec4) at offset 0
      shader[mode]->enableAttributeArray(0);
      shader[mode]->setAttributeBuffer(0,GL_FLOAT,0,4,12*sizeof(float));
      //   Attribute 1:  vertex color (vec3) offset 7 floats
      shader[mode]->enableAttributeArray(1);
      shader[mode]->setAttributeBuffer(1,GL_FLOAT,7*sizeof(float),3,12*sizeof(float));
      //   Attribute 2:  vertex normal offset 4 floats
      shader[mode]->enableAttributeArray(2);
      shader[mode]->setAttributeBuffer(2,GL_FLOAT,4*sizeof(float),3,12*sizeof(float));
      //   Attribute 3:  terture coordinates offset 10 floats
      shader[mode]->enableAttributeArray(3);
      shader[mode]->setAttributeBuffer(3,GL_FLOAT,10*sizeof(float),2,12*sizeof(float));

      // Draw the cube
      glDrawArrays(GL_TRIANGLES,0,cube_size);

      //  Disable vertex arrays
      shader[mode]->disableAttributeArray(0);
      shader[mode]->disableAttributeArray(1);
      shader[mode]->disableAttributeArray(2);
      shader[mode]->disableAttributeArray(3);


      //  Unbind this buffer
      cube_buffer.release();

      // Back to fixed pipeline
      shader[mode]->release();
   }

   //  Axes for reference
   glColor3f(1,1,1);
   glBegin(GL_LINES);
   glVertex3f(0,0,0);
   glVertex3f(2,0,0);
   glVertex3f(0,0,0);
   glVertex3f(0,2,0);
   glVertex3f(0,0,0);
   glVertex3f(0,0,2);
   glEnd();
   glDisable(GL_DEPTH_TEST);
   renderText(2,0,0,"X");
   renderText(0,2,0,"Y");
   renderText(0,0,2,"Z");
}

//
//  Set OpenGL projection
//
void Hw04opengl::doProjection()
{
   //  Set fixed pipeline transformation
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   if (fov)
   {
      float zmin = dim/4;
      float zmax = 4*dim;
      float ydim = zmin*tan(fov*M_PI/360);
      float xdim = ydim*asp;
      glFrustum(-xdim,+xdim,-ydim,+ydim,zmin,zmax);
   }
   else
      glOrtho(-dim*asp, +dim*asp, -dim, +dim, -dim, +dim);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   //  Set GL4 transformation
   proj.setToIdentity();
   if (fov)
      proj.perspective(fov,asp,dim/4,4*dim);
   else
      proj.ortho(-dim*asp, +dim*asp, -dim, +dim, -dim, +dim);
}
