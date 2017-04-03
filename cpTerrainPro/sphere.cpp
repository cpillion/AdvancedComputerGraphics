#include "sphere.h"
#include <QVector>
#include <iostream>

sphere::sphere()
{
    createVert();
    doBuffer();
    setupVertexAttribs();
}

float sphereData[31536];

void sphere::createVert()
{
    QVector<GLfloat> ballVerts;
    for (int ph=-90;ph<90;ph+=5)
    {
       for (int th=0;th<=360;th+=5)
       {
          // Verticies and Normals
          ballVerts.append(Sin(th)*Cos(ph));
          ballVerts.append(Cos(th)*Cos(ph));
          ballVerts.append(Sin(ph));
          ballVerts.append(1.0);
          ballVerts.append(0.0);
          ballVerts.append(0.0);
          ballVerts.append(Sin(th)*Cos(ph+10));
          ballVerts.append(Cos(th)*Cos(ph+10));
          ballVerts.append(Sin(ph+10));
          ballVerts.append(1.0);
          ballVerts.append(0.0);
          ballVerts.append(0.0);
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
    f->glEnableVertexAttribArray(1);
    f->glEnableVertexAttribArray(2);
    f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
    f->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), reinterpret_cast<void *>(3 * sizeof(GLfloat)));
    f->glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
    sphereBuffer.release();
}

QOpenGLBuffer sphere::getBuffer()
{
    return sphereBuffer;
}
