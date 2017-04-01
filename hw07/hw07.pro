#  Ubuntu:  apt-get install qtmultimedia5-dev libqt5multimedia5-plugins
HEADERS = hw07viewer.h hw07opengl.h hw07frame.h Type.h Object.h Cube.h Sphere.h Teapot.h CUgl.h
SOURCES = hw07.cpp hw07viewer.cpp hw07opengl.cpp hw07frame.cpp Object.cpp Cube.cpp Sphere.cpp Teapot.cpp CUgl.cpp
QT += opengl multimedia
RESOURCES = hw07.qrc
