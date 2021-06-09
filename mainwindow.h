#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QColorDialog>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_projector_cutOff_value_textEdited(const QString &arg1);

    void on_projector_pos_y_textEdited(const QString &arg1);

    void on_direct_x_slider_valueChanged(int value);

    void on_direct_y_slider_valueChanged(int value);

    void on_direct_z_slider_valueChanged(int value);

    void on_point_x_value_textEdited(const QString &arg1);

    void on_point_y_value_textEdited(const QString &arg1);

    void on_point_z_value_textEdited(const QString &arg1);

    void on_direct_intensity_valueChanged(int value);

    void on_point_intensity_valueChanged(int value);

    void on_projectot_intensity_valueChanged(int value);

    void on_direct_change_color_button_clicked();

    void on_point_change_color_button_clicked();

    void on_projector_change_color_button_clicked();

private:
    Ui::MainWindow *ui;
    QColorDialog* colorDialog;

    void disconect_color_dialog();
};

#endif // MAINWINDOW_H
