//
//  hw03.cpp
//  Homework 3: Performance
//  CSCI 5239 Spring 2017
//
//  Description: Investigate the performance of different elements of GLSL.
//
//  Created by Chris Pillion on 2/7/17.
//  Copyright © 2017 University of Colorado - CPillion. All rights reserved.
//

#include <QApplication>
#include "hw03viewer.h"

//
//  Main function
//
int main(int argc, char *argv[])
{
   //  Create the application
   QApplication app(argc,argv);
   //  Create and show view widget
   Hw03viewer view;
   view.show();
   //  Main loop for application
   return app.exec();
}
