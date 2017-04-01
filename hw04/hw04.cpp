//
//  hw04.cpp
//  Homework 4: OpenGL 3 and 4
//  CSCI 5239 Spring 2017
//
//  Description: Create a program that uses shaders in the OpenGL 3 or 4 style, that is using the
//  in and out qualifiers to pass variables into or between shaders and pass variables 
//  such as the transformation matrices and light properties into the shader as uniforms.
//
//  Created by Chris Pillion on 2/12/17.
//  Copyright © 2017 University of Colorado - CPillion. All rights reserved.
//

#include <QApplication>
#include <QGLFormat>
#include "hw04viewer.h"

//
//  Main function
//
int main(int argc, char *argv[])
{
   //  Create the application
   QApplication app(argc,argv);

   QGLFormat glFormat;
   glFormat.setVersion( 4, 0 );
   glFormat.setProfile( QGLFormat::CoreProfile) ;
   QGLFormat::setDefaultFormat(glFormat);

   //  Create and show view widget
   Hw04viewer view;
   view.show();
   //  Main loop for application
   return app.exec();
}
