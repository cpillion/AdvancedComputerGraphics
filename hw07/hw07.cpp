//
//  hw07.cpp
//  Homework 7: Image Processing
//  CSCI 5239 Spring 2017
//
//  Description: Create a program that performs image processing using GLSL.
//
//  Created by Chris Pillion on 3/5/17.
//  Copyright © 2017 University of Colorado - CPillion. All rights reserved.
//

#include <QApplication>
#include "hw07viewer.h"

//
//  Main function
//
int main(int argc, char *argv[])
{
   //  Create the application
   QApplication app(argc,argv);
   //  Create and show view widget
   Hw07viewer view;
   view.show();
   //  Main loop for application
   return app.exec();
}
