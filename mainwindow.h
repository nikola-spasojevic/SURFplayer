#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <player.h>
#include <mouse_tracker.h>
#include <QTime>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    /**************** FRAME PROCESSING ****************/
    //Display video frame in player UI
    void updatePlayerUI(QImage img);
    //Display the processed frame in the second window
    void processedPlayerUI(QImage processedImg);
    //Print contour Moments, Areas and lengths
    void contourDisplayUI(QString contour);
    /**************** FRAME PROCESSING ****************/

    /**************** PLAYER ****************/
    //Slot for the load video push button.
    void on_pushButton_clicked();
    // Slot for the play push button.
    void on_pushButton_2_clicked();
    QString getFormattedTime(int timeInSeconds);
    void on_horizontalSlider_sliderPressed();
    void on_horizontalSlider_sliderReleased();
    void on_horizontalSlider_sliderMoved(int position);
    /**************** PLAYER ****************/

    /**************** MOUSE TRACKER ****************/
    void Mouse_current_pos();
    void Mouse_pressed();
    void Mouse_left();
    void Mouse_PressAndHold();
    /**************** MOUSE TRACKER ****************/

private:
    Ui::MainWindow *ui;
    Player* myPlayer;
};

#endif // MAINWINDOW_H
