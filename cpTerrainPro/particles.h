#ifndef PARTICLES_H
#define PARTICLES_H

#include <QOpenGLFunctions>
#include <QOpenGLBuffer>

class particles
{
private:
    int N;
    float*  Vert;      //  Vertices
    float*  Color;     //  Colors
    float*  Vel;       //  Velocities
    float*  Start;     //  Start time
    QOpenGLBuffer partBuffer;
public:
    particles();
    void InitPart();
    QOpenGLBuffer getBuffer();
    void doBuffer();
    void setupVertexAttribs();
};

#endif // PARTICLES_H
