#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <mouse_tracker.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    /**************** FRAME PROCESSING ****************/
    myPlayer = new Player();
    QObject::connect(myPlayer, SIGNAL(originalImage(QImage)), this, SLOT(updatePlayerUI(QImage)));
    QObject::connect(myPlayer, SIGNAL(processedImage(QImage)), this, SLOT(processedPlayerUI(QImage)));
    QObject::connect(myPlayer, SIGNAL(countors(QString)), this, SLOT(contourDisplayUI(QString)));
    /**************** FRAME PROCESSING ****************/

    ui->setupUi(this);
    ui->pushButton_2->setEnabled(false);
    ui->horizontalSlider->setEnabled(false);

    /**************** MOUSE TRACKING ****************/
    QWidget::connect(ui->label, SIGNAL(Mouse_Pos()), this, SLOT(Mouse_current_pos()));
    QWidget::connect(ui->label, SIGNAL(Mouse_Pressed()), this, SLOT(Mouse_pressed()));
    QWidget::connect(ui->label, SIGNAL(Mouse_Left()), this, SLOT(Mouse_left()));
    QWidget::connect(ui->label, SIGNAL(Mouse_Release()), this, SLOT(Mouse_PressAndHold()));
    /**************** MOUSE TRACKING ****************/
}

void MainWindow::updatePlayerUI(QImage img)
{
    if (!img.isNull())
    {
        ui->label->setAlignment(Qt::AlignCenter);
        ui->label->setPixmap(QPixmap::fromImage(img).scaled(ui->label->size(), Qt::KeepAspectRatio, Qt::FastTransformation));

        ui->horizontalSlider->setValue(myPlayer->getCurrentFrame());
        ui->label_2->setText( getFormattedTime( (int)myPlayer->getCurrentFrame()/(int)myPlayer->getFrameRate()) );
    }
}

void MainWindow::processedPlayerUI(QImage processedImg)
{
    if (!processedImg.isNull())
    {
        ui->label_4->setAlignment(Qt::AlignCenter);
        ui->label_4->setPixmap(QPixmap::fromImage(processedImg).scaled(ui->label->size(),
                                                              Qt::KeepAspectRatio, Qt::FastTransformation));
    }
}

void MainWindow::contourDisplayUI(QString contour)
{
    //ui->plainTextEdit->appendPlainText(contour);
}

MainWindow::~MainWindow()
{
    delete myPlayer;
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    if (myPlayer->isStopped())
        {
            myPlayer->Play();
            ui->pushButton_2->setText(tr("Stop"));
        }else
        {
            myPlayer->Stop();
            ui->pushButton_2->setText(tr("Play"));
        }
}

void MainWindow::on_pushButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,
                                              tr("Open Video"), ".",
                                              tr("Video Files (*.avi *.mpg *.mp4)"));
    QFileInfo name = filename;

    if (!filename.isEmpty())
    {
        if (!myPlayer->loadVideo(filename.toLatin1().data()))
        {
            QMessageBox msgBox;
            msgBox.setText("The selected video could not be opened!");
            msgBox.exec();
        }
        else
        {
           this->setWindowTitle(name.fileName());
           ui->pushButton_2->setEnabled(true);
           ui->horizontalSlider->setEnabled(true);
           ui->horizontalSlider->setMaximum(myPlayer->getNumberOfFrames());
           ui->label_3->setText( getFormattedTime( (int)myPlayer->getNumberOfFrames()/(int)myPlayer->getFrameRate()) );
       }
    }
}

QString MainWindow::getFormattedTime(int timeInSeconds){

    int seconds = (int) (timeInSeconds) % 60 ;
    int minutes = (int) ((timeInSeconds / 60) % 60);
    int hours   = (int) ((timeInSeconds / (60*60)) % 24);

    QTime t(hours, minutes, seconds);
    if (hours == 0 )
        return t.toString("mm:ss");
    else
        return t.toString("h:mm:ss");
}

void MainWindow::on_horizontalSlider_sliderPressed()
{
    myPlayer->Stop();
}

void MainWindow::on_horizontalSlider_sliderReleased()
{
    myPlayer->Play();
}

void MainWindow::on_horizontalSlider_sliderMoved(int position)
{
    myPlayer->setCurrentFrame(position);
    ui->label_2->setText( getFormattedTime( position/(int)myPlayer->getFrameRate()) );
}

void MainWindow::Mouse_current_pos()
{   
    ui->label->left = false;
    QString coord =  QString("X = ") + QString::number(ui->label->x) +  QString(" - Y = ") + QString::number(ui->label->y);
    ui->plainTextEdit->appendPlainText(QString(coord));
}

void MainWindow::Mouse_pressed()
{
    if (!ui->label->hasMouseLeft())
    {
        myPlayer->Stop();
    }
    //ui->plainTextEdit->appendPlainText(QString("Mouse Pressed!"));
}

void MainWindow::Mouse_left()
{
    ui->label->left = true;
    ui->plainTextEdit->appendPlainText(QString("Mouse Left!"));
}

void MainWindow::Mouse_PressAndHold()
{

}

