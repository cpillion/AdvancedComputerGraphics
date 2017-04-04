#include "particles.h"
#include <iostream>
#include <QVector>


//  Set up array indexes for program
const int VELOCITY_ARRAY=4;
const int START_ARRAY=5;
const char* Name = ",,,,Vel,Start";

/*
 *  Random numbers with range and offset
 */
static float frand(float rng,float off)
{
   return rand()*rng/RAND_MAX+off;
}

particles::particles()
{
    N = 50;
    InitPart();
    doBuffer();
    setupVertexAttribs();
}

float partInfo[9000];

/*
 *  Initialize particles
 */
void particles::InitPart(void)
{
   QVector<GLfloat> partData;
   //  Array Pointers
   float* vert  = Vert;
   float* color = Color;
   float* vel   = Vel;
   float* start = Start;
   //  Loop over NxN patch
   int n = N;
   int dim = 4;
   for (int i=0;i<n;i++)
      for (int j=0;j<n;j++)
      {
         //  Location x,y,z
         //  Spread snowfall out over twice the viewing plane
         partData.append(frand(2*dim, -dim));
         partData.append(2*dim);
         partData.append(frand(2*dim, -dim));
         //  Color r,g,b (0.5-1.0)
         partData.append(frand(0.5,0.5));
         partData.append(frand(0.5,0.5));
         partData.append(frand(0.5,0.5));
         //  Velocity
         partData.append(frand( 0.0,0.0));
         partData.append(frand( 0.0,0.0));
         partData.append(frand( 0.0,0.0));
         //  Launch time
         partData.append(frand(2*dim,0.0));
      }
   for (int i = 0; i<partData.size(); i++)
       partInfo[i] = partData.at(i);
}

void particles::doBuffer()
{
    partBuffer.create();
    partBuffer.bind();
    partBuffer.allocate(partInfo, sizeof(partInfo));

}

void particles::setupVertexAttribs()
{
    partBuffer.bind();
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    f->glEnableVertexAttribArray(0);
    f->glEnableVertexAttribArray(1);
    f->glEnableVertexAttribArray(4);
    f->glEnableVertexAttribArray(5);
    f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 10 * sizeof(GLfloat), 0);
    f->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 10 * sizeof(GLfloat), reinterpret_cast<void *>(3 * sizeof(GLfloat)));
    f->glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 10 * sizeof(GLfloat), reinterpret_cast<void *>(6 * sizeof(GLfloat)));
    f->glVertexAttribPointer(5, 1, GL_FLOAT, GL_FALSE, 10 * sizeof(GLfloat), reinterpret_cast<void *>(9 * sizeof(GLfloat)));
    partBuffer.release();
}

QOpenGLBuffer particles::getBuffer()
{
    return partBuffer;
}

