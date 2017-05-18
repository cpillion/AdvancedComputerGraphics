#include "particles.h"
#include <iostream>
#include <QVector>


//  Set up array indexes for program
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
    N = 40;
    InitPart();
    doBuffer();
    setupVertexAttribs();
}

float partInfo[11200];

/*
 *  Initialize particles
 */
void particles::InitPart(void)
{
   QVector<GLfloat> partData;
   //  Loop over NxN patch
   int n = N;
   int dim = 4;
   for (int i=0;i<n;i++)
      for (int j=0;j<n;j++)
      {
         //  Location x,y,z
         //  Spread snowfall out over the viewing plane
         partData.append(frand(2*dim, -dim));
         partData.append(2*dim);
         partData.append(frand(2*dim, -dim));
         //  Velocity
         partData.append(frand( 0.0,0.0));
         partData.append(frand( 0.0,0.0));
         partData.append(frand( 0.0,0.0));
         //  Launch time
         partData.append(frand(1.5*dim,0.0));
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
    f->glEnableVertexAttribArray(4);
    f->glEnableVertexAttribArray(5);
    f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), 0);
    f->glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), reinterpret_cast<void *>(3 * sizeof(GLfloat)));
    f->glVertexAttribPointer(5, 1, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), reinterpret_cast<void *>(6 * sizeof(GLfloat)));
    partBuffer.release();
}

QOpenGLBuffer particles::getBuffer()
{
    return partBuffer;
}

