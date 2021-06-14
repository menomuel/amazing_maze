#include <QApplication>

#include <QColorDialog>
#include <QLabel>
#include <QSurfaceFormat>
#include <QWidget>

#include "cubewidget.h"
#include "mainwindow.h"

#include <random>

int gen_rand(double min, double max, int seed = 0)
{
    std::default_random_engine gen{seed};
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
}



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
