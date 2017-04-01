//
//  hw08.cpp
//  Homework 8: Textures for Data Storage
//  CSCI 5239 Spring 2017
//
//  Description: Create a program using GLSL that uses textures for data storage.
//
//  Created by Chris Pillion on 3/13/17.
//  Copyright © 2017 University of Colorado - CPillion. All rights reserved.
//

#include <QApplication>
#include "hw08viewer.h"

//
//  Main function
//
int main(int argc, char *argv[])
{
   //  Create the application
   QApplication app(argc,argv);
   //  Create and show view widget
   Hw08viewer view;
   view.show();
   //  Main loop for application
   return app.exec();
}
