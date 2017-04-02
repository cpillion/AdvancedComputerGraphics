#ifndef PARTICLES_H
#define PARTICLES_H

#include <QOpenGLFunctions>

class particles
{
private:
    int N;
    float*  Vert;      //  Vertices
    float*  Color;     //  Colors
    float*  Vel;       //  Velocities
    float*  Start;     //  Start time
public:
    particles();
    void InitPart();
    void DrawPart();
};

#endif // PARTICLES_H
