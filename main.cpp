#include <QApplication>

#include <QColorDialog>
#include <QLabel>
#include <QSurfaceFormat>
#include <QWidget>

#include "cubewidget.h"
#include "mainwindow.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    QSurfaceFormat::setDefaultFormat(format);

    app.setApplicationName("cube_lighting");

    MainWindow window;

    window.show();

    return app.exec();
}
