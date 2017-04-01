//
//  OpenGL widget
//
#include "hw08opengl.h"
#include "Plane.h"
#include <math.h>

//
//  Constructor
//
Hw08opengl::Hw08opengl(QWidget* parent)
    : CUgl(parent,false)
{
   mode = 0;
   MAP_SCALE = 2.0;
   H_SCALE = 0.75;
}

//
//  Set mode
//
void Hw08opengl::setMode(int m)
{
   mode = m;
   //  Request redisplay
   update();
}

//
//  Set position
//
void Hw08opengl::setMsize(int s)
{
   MAP_SCALE = 0.1*s;
   //  Request redisplay
   InitializeTerrain();
   update();
}

void Hw08opengl::setHsize(int s)
{
   H_SCALE = 0.1*s;
   //  Request redisplay
   InitializeTerrain();
   update();
}

//
//  Initialize
//
void Hw08opengl::initializeGL()
{
   //  Set Dimension
   setDim(150*MAP_SCALE);

   //  Load shaders
   addShader(":/hw08.vert",":/hw08.frag");

   //  Load textures
   hMap  = LoadTexBMP("heightmap.bmp");
   rock  = loadImage("rock.jpg");
   snow  = loadImage("snow.jpg");
   norm  = loadImage("normMap.png");
   grass = loadImage("grass.jpg");
   alpha = InitializeTerrain(); // Alpha Map
}


unsigned int Hw08opengl::InitializeTerrain()
{
   unsigned int vertexTexture;
   float texpct[MAP_X*MAP_Z*3];
    // Loop through all of the heightfield points, calculating
    // the coordinates for each point
    for (int z = 0; z < MAP_Z; z++)
    {
        for (int x = 0; x < MAP_X; x++)
        {
            // Generate Vertices
            terrain[x][z][0] = float(x)*MAP_SCALE;
            terrain[x][z][1] = (float)hMap[(z*MAP_Z+x)*3]*H_SCALE;
            terrain[x][z][2] = -float(z)*MAP_SCALE;
            // Create Alpha Texture for multitexture blending in fragment shader
            texpct[3*(x+z*MAP_Z)+0] = (terrain[x][z][1]/H_SCALE/255.>=0.0 && terrain[x][z][1]/H_SCALE/255.<0.475)? 1.0: 0.0;
            texpct[3*(x+z*MAP_Z)+1] = (terrain[x][z][1]/H_SCALE/255.>=0.475 && terrain[x][z][1]/H_SCALE/255.<0.575)? 1.0: 0.0;
            texpct[3*(x+z*MAP_Z)+2] = (terrain[x][z][1]/H_SCALE/255.>=0.575 && terrain[x][z][1]/H_SCALE/255.<1.0)? 1.0: 0.0;
        }
    }

    // Save alpha texture data to a 2D texture and lineraly interpolate
    glGenTextures(1, &vertexTexture);  
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, vertexTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, MAP_X, MAP_Z, 0, GL_RGB, GL_FLOAT, texpct);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    return vertexTexture;
}


void Hw08opengl::DrawTerrain()
{
   glPushMatrix();
   glTranslated(-128*MAP_SCALE, -128*H_SCALE, 128*MAP_SCALE);
    for (int z = 0; z < MAP_Z-1; z++)
    {
        glBegin(GL_TRIANGLE_STRIP);
        for (int x = 0; x < MAP_X-1; x++)
        {
            // Color based on greyscale values
            glColor3f((terrain[x][z][1]/H_SCALE)/255.0f, 
                      (terrain[x][z][1]/H_SCALE)/255.0f, 
                      (terrain[x][z][1]/H_SCALE)/255.0f);
            // Texture coordinates spread along image size
            glTexCoord2f(float(x)/MAP_X, float(z)/MAP_Z);
            glVertex3f(terrain[x][z][0], 
                       terrain[x][z][1], terrain[x][z][2]);

            glTexCoord2f((float(x)+1)/MAP_X, float(z)/MAP_Z);
            glColor3f((terrain[x+1][z][1]/H_SCALE)/255.0f, 
                      (terrain[x+1][z][1]/H_SCALE)/255.0f, 
                      (terrain[x+1][z][1]/H_SCALE)/255.0f);
            glVertex3f(terrain[x+1][z][0], terrain[x+1][z][1], 
                       terrain[x+1][z][2]);

            glTexCoord2f(float(x)/MAP_X, (float(z)+1)/MAP_Z);
            glColor3f((terrain[x][z+1][1]/H_SCALE)/255.0f, 
                      (terrain[x][z+1][1]/H_SCALE)/255.0f, 
                      (terrain[x][z+1][1]/H_SCALE)/255.0f);
            glVertex3f(terrain[x][z+1][0], terrain[x][z+1][1], 
                       terrain[x][z+1][2]);

            glColor3f((terrain[x+1][z+1][1]/H_SCALE)/255.0f, 
                      (terrain[x+1][z+1][1]/H_SCALE)/255.0f, 
                      (terrain[x+1][z+1][1]/H_SCALE)/255.0f);
            glTexCoord2f((float(x)+1)/MAP_X, (float(z)+1)/MAP_Z);
            glVertex3f(terrain[x+1][z+1][0], 
                       terrain[x+1][z+1][1], 
                       terrain[x+1][z+1][2]);
        }
        glEnd();
    }
    glPopMatrix();

}

//
//  Draw the window
//
void Hw08opengl::paintGL()
{

   //  Z-buffer
   glEnable(GL_DEPTH_TEST);
   //  Clear screen and depth buffer
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   doProjection();
   setPerspective(1);
   //  Set view
   doView();

   //  Set light
   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   glEnable(GL_NORMALIZE);
   float Ambient[]  = {0.1,0.1,0.1,1.0};
   float Diffuse[]  = {0.3,0.3,0.3,1.0};
   float Specular[] = {1.0,1.0,1.0,1.0};
   glLightfv(GL_LIGHT0,GL_AMBIENT ,Ambient);
   glLightfv(GL_LIGHT0,GL_DIFFUSE ,Diffuse);
   glLightfv(GL_LIGHT0,GL_SPECULAR,Specular);
   //  Light color and direction
   float Position[]  = {0.0,-100.0,0.0,0.0};
   glLightfv(GL_LIGHT0,GL_POSITION,Position);

   //  Texture for this month
   glActiveTexture(GL_TEXTURE0);
   glBindTexture(GL_TEXTURE_2D,rock);
   //  Texture for next month
   glActiveTexture(GL_TEXTURE1);
   glBindTexture(GL_TEXTURE_2D,snow);
   //  Load nightime texture
   glActiveTexture(GL_TEXTURE2);
   glBindTexture(GL_TEXTURE_2D,alpha);
   //  Load cloud, gloss and elevation texture
   glActiveTexture(GL_TEXTURE3);
   glBindTexture(GL_TEXTURE_2D,grass);
   //  Reset texture unit
   glActiveTexture(GL_TEXTURE0);

   //  Enable shader
   if (mode) 
   {
      shader[0]->bind();

   //  Set shader increments
      shader[0]->setUniformValue("normalmap",norm);
      shader[0]->setUniformValue("RockTex" ,0);
      shader[0]->setUniformValue("SnowTex" ,1);
      shader[0]->setUniformValue("alphaTex",2);
      shader[0]->setUniformValue("GrassTex",3);

      //objects[0]->setRotate(0,0,1,0);
      DrawTerrain();

      doScene();

   //  Enable shader
      shader[0]->release();
   }
   //  Disable lighting
   glDisable(GL_LIGHTING);

   if (!mode) DrawTerrain();
}
