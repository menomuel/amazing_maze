#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    colorDialog(new QColorDialog(this))
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_projector_cutOff_value_textEdited(const QString &textAngle)
{
    ui->cubewidget->projectorLightCutOffChange(textAngle.toFloat());
}

void MainWindow::on_projector_pos_y_textEdited(const QString &textAngle)
{
    ui->cubewidget->projectorLightOuterCutOffChange(textAngle.toFloat());
}

void MainWindow::on_direct_x_slider_valueChanged(int value)
{
    int range = ui->direct_x_slider->maximum() - ui->direct_x_slider->minimum();
    float validValue = 1.f * (value - range/2) / (range/2);
    ui->cubewidget->directLightChangeX(validValue);
}

void MainWindow::on_direct_y_slider_valueChanged(int value)
{
    int range = ui->direct_y_slider->maximum() - ui->direct_y_slider->minimum();
    float validValue = 1.f * (value - range/2) / (range/2);
    ui->cubewidget->directLightChangeY(validValue);
}



void MainWindow::on_direct_z_slider_valueChanged(int value)
{
    int range = ui->direct_z_slider->maximum() - ui->direct_z_slider->minimum();
    float validValue = 1.f * (value - range/2) / (range/2);
    ui->cubewidget->directLightChangeZ(validValue);
}

void MainWindow::on_point_x_value_textEdited(const QString &textX)
{
    ui->cubewidget->pointLightChangeX(textX.toFloat());
}

void MainWindow::on_point_y_value_textEdited(const QString &textY)
{
    ui->cubewidget->pointLightChangeY(textY.toFloat());
}

void MainWindow::on_point_z_value_textEdited(const QString &textZ)
{
    ui->cubewidget->pointLightChangeZ(textZ.toFloat());
}

void MainWindow::on_direct_intensity_valueChanged(int value)
{
    float validValue = 1.f * (ui->direct_intensity->maximum() - value) / (ui->direct_intensity->maximum() - ui->direct_intensity->minimum());
    ui->cubewidget->directLightIntensityChange(validValue);

}

void MainWindow::on_point_intensity_valueChanged(int value)
{
    float validValue = 1.f * (ui->direct_intensity->maximum() - value) / (ui->direct_intensity->maximum() - ui->direct_intensity->minimum());
    ui->cubewidget->pointLightIntensityChange(validValue);
}

void MainWindow::on_projectot_intensity_valueChanged(int value)
{
    float validValue = 1.f * (ui->direct_intensity->maximum() - value) / (ui->direct_intensity->maximum() - ui->direct_intensity->minimum());
    ui->cubewidget->projectorLightIntensityChange(validValue);
}

void MainWindow::on_direct_change_color_button_clicked()
{
    disconect_color_dialog();
    QObject::connect(colorDialog, &QColorDialog::currentColorChanged, ui->cubewidget, &CubeWidget::directLightColorChange);
    colorDialog->show();
}

void MainWindow::on_point_change_color_button_clicked()
{
    disconect_color_dialog();
    QObject::connect(colorDialog, &QColorDialog::currentColorChanged, ui->cubewidget, &CubeWidget::pointLightColorChange);
    colorDialog->show();
}

void MainWindow::on_projector_change_color_button_clicked()
{
    disconect_color_dialog();
    QObject::connect(colorDialog, &QColorDialog::currentColorChanged, ui->cubewidget, &CubeWidget::projectorLightColorChange);
    colorDialog->show();
}

void MainWindow::disconect_color_dialog()
{
    QObject::disconnect(colorDialog, &QColorDialog::currentColorChanged, ui->cubewidget, &CubeWidget::directLightColorChange);
    QObject::disconnect(colorDialog, &QColorDialog::currentColorChanged, ui->cubewidget, &CubeWidget::pointLightColorChange);
    QObject::disconnect(colorDialog, &QColorDialog::currentColorChanged, ui->cubewidget, &CubeWidget::projectorLightColorChange);
}
