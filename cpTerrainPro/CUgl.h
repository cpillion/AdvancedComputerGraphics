//
//  CU OpenGL Widget for Modern OpenGL
//

#ifndef CUGL_H
#define CUGL_H

#include <QApplication>
#include <QOpenGLWidget>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QString>
#include <QVector>
#include <QMouseEvent>
#include <QTimer>
#include <QElapsedTimer>
#include <QMessageBox>
#include <QObject>
#include <QKeyEvent>
#include "math.h"
#include "Object.h"

class CUgl : public QOpenGLWidget
{
Q_OBJECT
private:
   float            La,Ld,Ls; // Light intensity
   float            Lr;       // Light radius
   float            zh;       // Light angle
   float            ylight;   // Light elevation
   bool             move;     // Moving light
   int              obj;      // Selected Object
   QTimer           timer;    // Timer for animations
protected:
   QElapsedTimer    time;     // Track elapsed time
   QVector<Object*> objects;  // Objects
   bool             mouse;    // Mouse pressed
   QPoint           pos;      // Mouse position
   int              fov;      // Field of view
   float            Dim;      // Default size
   float            dim;      // Display size
   float            asp;      // Sceen aspect ratio
   int              th,ph;    // Camera angles
   float              x, y, z;  // Camera Position
   int              mode;     // Selected shader
   QMatrix4x4       proj;
   QMatrix4x4       viewPortMat;
   QVector<QOpenGLShaderProgram*> shader; // Shaders

public:
   CUgl(QWidget* parent=0);        // Constructor
   QSize sizeHint() const {return QSize(400,400);} // Default size of widget
public slots:
   void reset();
   void setDim(float d);                            // Set scene size
   void setPerspective(int on);                     // Set perspective
   void setShader(int sel);                         // Set shader
   void setObject(int type);                        // Set displayed object
   void addObject(Object* obj);                     // Add object
   void doScene();                                  // Draw scene
   void setLightMove(bool on);                      // Set light animation
   void setLightAngle(int th);                      // Set light angle
   void setLightElevation(int pct);                 // Set light elevation (percent)
   void setLightIntensity(float a,float d,float s); // Set light intensity
   void maxFPS(bool);                               // Set max fps
   void addShader(QString vert,QString frag,QString names=""); // Add shader
   void addShader3(QString vert,QString geom,QString frag);    // Add shader
   void addShaderTess(QString vert, QString tcs, QString tes, QString geom, QString frag, QString names);    // Add shader
protected:
   void initializeGL();                             // Initialization
   void resizeGL(int,int);                          // Window resize
   void mousePressEvent(QMouseEvent*);              // Mouse pressed
   void mouseReleaseEvent(QMouseEvent*);            // Mouse released
   void mouseMoveEvent(QMouseEvent*);               // Mouse moved
   void wheelEvent(QWheelEvent*);                   // Mouse wheel
   void keyPressEvent( QKeyEvent* );
   void Fatal(QString message);                     // Error handler
   QMatrix4x4 doView();                                   // Apply modelview
   QVector4D doLight();                             // Enable light
   void doProjection();                             // Update projection
   float getTime() {return 0.001*time.elapsed();}   // Elapsed time in seconds
   unsigned char* LoadTexBMP(const char* file);
   void Reverse(void* x,const int n);
private slots:
   void tick();                                     // Method to capture timer ticks
signals:
   void light(int angle);                           // Signal for light angle
   void angles(QString text);                       // Signal for view angles
};

#endif
