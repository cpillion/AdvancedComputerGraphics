//
//  hw01.cpp
//  Homework 1: NDC to RGB shader
//  CSCI 4239/5239 Spring 2017
//
//  Description: The color of every vertex in every object should be set using a shader such that the
//  coordinates of the vertex in Normalized Device Coordinates (-1 to +1 in x,y,z) determines the color of
//  the vertex.
//
//  Created by Chris Pillion on 1/24/17.
//  Copyright © 2017 University of Colorado - CPillion. All rights reserved.
//

#include <QApplication>
#include "hw01viewer.h"


//  Main function
int main(int argc, char *argv[])
{
   //  Create the application
   QApplication app(argc,argv);
   //  Create and show view widget
   Hw01viewer view;
   view.show();
   //  Main loop for application
   return app.exec();
}
