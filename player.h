#ifndef PLAYER_H
#define PLAYER_H

#include <QMutex>
#include <QThread>
#include <QImage>
#include <QWaitCondition>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/calib3d/calib3d.hpp> // for homography
#include <opencv2/nonfree/nonfree.hpp>
using namespace cv;

class Player : public QThread
{    Q_OBJECT
 private:
    bool stop;
    QMutex mutex;
    QWaitCondition condition;
    Mat frame;
    Mat processedFrame;
    int frameRate;
    VideoCapture *capture;
    Mat RGBframe;
    QImage img;
    QImage imgProcessed;
 signals:
 //Signal to output frame to be displayed
      void originalImage(const QImage &image);
      void processedImage(const QImage &imgProcessed);
      void countors(const QString contour);
 protected:
     void run();
     void msleep(int ms);
 public:
    //Constructor
    Player(QObject *parent = 0);
    //Destructor
    ~Player();
    //Load a video from memory
    bool loadVideo(string filename);
    //Play the video
    void Play();
    //Stop the video
    void Stop();
    //check if the player has been stopped
    bool isStopped() const;
    //set video properties
    void setCurrentFrame(int frameNumber);
    //Get video properties
    double getFrameRate();
    double getCurrentFrame();
    double getNumberOfFrames();
    //Process frame image to find contours and send the signal along with the original frame
    void ProcessFrame();
    void SIFTFeatureDetector();
    void SURFFeatureDetector();
};

#endif // PLAYER_H
