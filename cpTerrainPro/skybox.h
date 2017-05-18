#ifndef SKYBOX_H
#define SKYBOX_H


#include <QOpenGLBuffer>
#include <QOpenGLFunctions>

class skybox
{
    const static int cubeSize = 36;
private:
    QOpenGLBuffer cubeBuffer;
    void setupVertexAttribs();
public:
    skybox();
    void doBuffer();
    QOpenGLBuffer getBuffer();
};


#endif // SKYBOX_H
