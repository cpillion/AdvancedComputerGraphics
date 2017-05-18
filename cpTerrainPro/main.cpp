//
//  cpTerrainPro.cpp
//  Final Project: Terrain Generation Using OpenGL 4 and Qt 5
//  CSCI 5239 Spring 2017
//
//  Description: Create a program using OpenGL and GLSL demonstrating knowledge of advanced computer graphics
//
//  Created by Chris Pillion on 5/3/17.
//  Copyright © 2017 University of Colorado - CPillion. All rights reserved.
//

#include <QApplication>
#include <QDesktopWidget>
#include <QSurfaceFormat>
#include "appWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QDesktopWidget dw;

    // Use QSurfaceFormat to define the OpenGL Core Profile and Version
    QSurfaceFormat fmt;
    // Max Version for the Intel HD 4000 Graphics Card
    fmt.setVersion(4, 1);
    fmt.setProfile(QSurfaceFormat::CoreProfile);
    QSurfaceFormat::setDefaultFormat(fmt);

    // Create a new instance of the application using the appWindow class
    appWindow view;
    // Size the window to 65% and 55% of screen size for initial viewing area
    view.resize(dw.width()*0.65, dw.height()*0.55);
    view.show();

    return app.exec();
}
