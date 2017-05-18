HEADERS       = \
    CUgl.h \
    Object.h \
    Type.h \
    oglWidget.h \
    particles.h \
    appWindow.h \
    cube.h \
    sphere.h \
    Noise.h \
    skybox.h
SOURCES       = \
                main.cpp \
    CUgl.cpp \
    Object.cpp \
    oglWidget.cpp \
    particles.cpp \
    appWindow.cpp \
    cube.cpp \
    sphere.cpp \
    Noise.cpp \
    skybox.cpp

QT           += widgets

RESOURCES += \
    cpTerrainPro.qrc

DISTFILES += \
    shaders/terrain.frag \
    shaders/terrain.vert
