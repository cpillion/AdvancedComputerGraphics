#ifndef PARTICLES_H
#define PARTICLES_H

#include <QOpenGLFunctions>
#include <QOpenGLBuffer>

class particles
{
private:
    int N;
    QOpenGLBuffer partBuffer;
public:
    particles();
    void InitPart();
    QOpenGLBuffer getBuffer();
    void doBuffer();
    void setupVertexAttribs();
};

#endif // PARTICLES_H
