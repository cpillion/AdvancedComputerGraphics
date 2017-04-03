#include "sphere.h"
#include <QVector>
#include <iostream>

sphere::sphere()
{
    createVert();
    doBuffer();
    setupVertexAttribs();
}

float sphereData[2052];

void sphere::createVert()
{
    QVector<GLfloat> ballVerts;
    for (int ph=-90;ph<90;ph+=10)
    {
       for (int th=0;th<=360;th+=20)
       {
          ballVerts.append(Sin(th)*Cos(ph));
          ballVerts.append(Cos(th)*Cos(ph));
          ballVerts.append(Sin(ph));
          ballVerts.append(Sin(th)*Cos(ph+10));
          ballVerts.append(Cos(th)*Cos(ph+10));
          ballVerts.append(Sin(ph+10));
       }
    }
    for (int i = 0; i<ballVerts.size(); i++)
        sphereData[i] = ballVerts.at(i);
}


void sphere::doBuffer()
{
    sphereBuffer.create();
    sphereBuffer.bind();
    sphereBuffer.allocate(sphereData, sizeof(sphereData));

}

void sphere::setupVertexAttribs()
{
    sphereBuffer.bind();
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    f->glEnableVertexAttribArray(0);
    f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
    sphereBuffer.release();
}

QOpenGLBuffer sphere::getBuffer()
{
    return sphereBuffer;
}
