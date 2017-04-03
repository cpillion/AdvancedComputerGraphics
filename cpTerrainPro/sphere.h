#ifndef SPHERE_H
#define SPHERE_H

#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include "math.h"
#define Cos(th) cos(M_PI/180*(th))
#define Sin(th) sin(M_PI/180*(th))

class sphere
{
    const static int sphereSize = 5256;
private:
    QOpenGLBuffer sphereBuffer;
    void setupVertexAttribs();
    void createVert();
public:
    sphere();
    void doBuffer();
    QOpenGLBuffer getBuffer();
};

#endif // SPHERE_H
