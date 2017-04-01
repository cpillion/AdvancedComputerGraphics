//
//  OpenGL Hw01opengl Widget
//

#ifndef HW01OPENGL_H
#define HW01OPENGL_H

#include <QtOpenGL>
#include <QString>
#include <QVector>
#include <QTimer>
#include <QElapsedTimer>
#include "Object.h"

class Hw01opengl : public QGLWidget
{
Q_OBJECT
private:
   bool    light;     //  Lighting
   int     mode;      //  Display mode
   int     th,ph;     //  Display angles
   int autoMove;      //  Box Bounce Option
   int     x0,y0,z0;  //  Object center (percent)
   bool    mouse;     //  Mouse pressed
   QPoint  pos;       //  Mouse position
   int     fov;       //  Field of view
   double  dim;       //  Display size
   double  asp;       //  Sceen aspect ratio
   Object* obj;       //  Object
   QTimer           timer;   //  Timer for animations
   QElapsedTimer    time;    //  Track elapsed time
   QGLShaderProgram shader;  //  Shader
   QVector<Object*> objects; //  Objects
public:
   Hw01opengl(QWidget* parent=0);                  //  Constructor
   QSize sizeHint() const {return QSize(400,400);} //  Default size of widget
public slots:
    void setShader(int on);                //  Slot to set shader
    void setPerspective(int on);           //  Slot to set projection type
    void setObject(int type);              //  Slot to set displayed object
    void setLighting(int on);              //  Slot to set lighting
    void setX(int X);                      //  Slot to set X position (percent)
    void setY(int Y);                      //  Slot to set Y position (percent)
    void setZ(int Z);                      //  Slot to set Z position (percent)
    void setMove(int on);                  //  Slot to set movement
signals:
    void angles(QString text);             //  Signal for view angles
    void center(QString text);             //  Signal for view position
protected:
    void initializeGL();                   //  Initialize widget
    void resizeGL(int width, int height);  //  Resize widget
    void paintGL();                        //  Draw widget
    void mousePressEvent(QMouseEvent*);    //  Mouse pressed
    void mouseReleaseEvent(QMouseEvent*);  //  Mouse released
    void mouseMoveEvent(QMouseEvent*);     //  Mouse moved
    void wheelEvent(QWheelEvent*);         //  Mouse wheel
private:
   void Fatal(QString message);            //  Error handler
   void Projection();                      //  Update projection
};

#endif
