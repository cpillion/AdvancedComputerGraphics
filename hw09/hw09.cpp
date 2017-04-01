//
//  hw09.cpp
//  Homework 9: Advanced Shaders
//  CSCI 5239 Spring 2017
//
//  Description: Implement a particle engine or an advanced shader such 
//  as a geometry, tesselation or compute shader.
//
//  Created by Chris Pillion on 3/20/17.
//  Copyright © 2017 University of Colorado - CPillion. All rights reserved.
//

#include <QApplication>
#include "hw09viewer.h"

//
//  Main function
//
int main(int argc, char *argv[])
{
   //  Create the application
   QApplication app(argc,argv);
   //  Create and show view widget
   Hw09viewer view;
   view.show();
   //  Main loop for application
   return app.exec();
}
