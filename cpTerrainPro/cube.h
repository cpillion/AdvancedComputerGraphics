#ifndef CUBE_H
#define CUBE_H

#include <QOpenGLBuffer>
#include <QOpenGLFunctions>

class cube
{
    const static int cubeSize = 36;
private:
    QOpenGLBuffer cubeBuffer;
    void setupVertexAttribs();
public:
    cube();
    void doBuffer();
    QOpenGLBuffer getBuffer();
};

#endif // CUBE_H
