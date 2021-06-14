QT       += core gui \
            multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    arrow.cpp \
    camera.cpp \
    cube.cpp \
    cubewidget.cpp \
    main.cpp \
    mainwindow.cpp \
    maze_generator.cpp \
    meshfactory.cpp \
    pathfinder.cpp \
    rect.cpp \
    renderobject.cpp \
    scene.cpp \
    texture.cpp

HEADERS += \
    arrow.h \
    camera.h \
    cube.h \
    cubewidget.h \
    mainwindow.h \
    maze_generator.h \
    mesh.h \
    meshfactory.h \
    pathfinder.h \
    rect.h \
    renderobject.h \
    scene.h \
    texture.h \
    types.h \
    vertex.h

LIBS += -lopengl32

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    media.qrc \
    shaders.qrc
