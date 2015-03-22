#include "player.h"

Player::Player(QObject *parent)
 : QThread(parent)
{
    stop = true;
}

bool Player::loadVideo(string filename) {
    capture  =  new cv::VideoCapture(filename);

    if (capture->isOpened())
    {
        frameRate = (int) capture->get(CV_CAP_PROP_FPS);
        return true;
    }
    else
        return false;
}

void Player::Play()
{
    if (!isRunning()) {
        if (isStopped()){
            stop = false;
        }
        start(LowPriority);
    }
}

void Player::run()
{
    int delay = (1000/frameRate);
    while(!stop)
    {
        if (!capture->read(frame))
        {
            stop = true;
        }
        if (frame.channels()== 3)
        {
            cv::cvtColor(frame, frame, CV_BGR2RGB);

            SURFFeatureDetector();
            //ProcessFrame();
            img = QImage((const unsigned char*)(frame.data),
                              frame.cols,frame.rows,QImage::Format_RGB888);
            //frame = RGBframe;

            imgProcessed = QImage((const unsigned char*)(processedFrame.data),
                                  processedFrame.cols,processedFrame.rows,QImage::Format_RGB888);
        }
        else
        {
            SURFFeatureDetector();
            //ProcessFrame();

            img = QImage((const unsigned char*)(frame.data),
                                 frame.cols,frame.rows,QImage::Format_Indexed8);

            imgProcessed = QImage((const unsigned char*)(processedFrame.data),
                                  processedFrame.cols,processedFrame.rows,QImage::Format_Indexed8);
        }

        emit originalImage(img);
        emit processedImage(imgProcessed);

        this->msleep(delay);
    }
}

Player::~Player()
{
    mutex.lock();
    stop = true;
    capture->release();
    delete capture;
    condition.wakeOne();
    mutex.unlock();
    wait();
}

void Player::Stop()
{
    stop = true;
}

void Player::msleep(int ms){
    struct timespec ts = { ms / 1000, (ms % 1000) * 1000 * 1000 };
    nanosleep(&ts, NULL);
}

bool Player::isStopped() const{
    return this->stop;
}

double Player::getCurrentFrame()
{
    return capture->get(CV_CAP_PROP_POS_FRAMES);
}

double Player::getNumberOfFrames()
{
    return capture->get(CV_CAP_PROP_FRAME_COUNT);
}

double Player::getFrameRate()
{
    return frameRate;
}

void Player::setCurrentFrame( int frameNumber )
{
    capture->set(CV_CAP_PROP_POS_FRAMES, frameNumber);
}

/**************** Contours and Convex Hulls ****************/
void Player::ProcessFrame()
{
    Mat src_gray;
    Mat canny_output;
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    const int thresh = 100;
    const int max_thresh = 255;
    RNG rng(12345);

    cvtColor(frame, src_gray, CV_BGR2GRAY );
    blur( src_gray, src_gray, Size(3,3) );

    /// Detect edges using canny
    Canny( src_gray, canny_output, thresh, max_thresh , 3 );

    /// Find contours
    findContours( canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

    /// Get the moments
    vector<Moments> mu(contours.size() );
    for( int i = 0; i < contours.size(); i++ )
        mu[i] = moments( contours[i], false );

    ///  Get the mass centers:
    vector<Point2f> mc( contours.size() );
    for( int i = 0; i < contours.size(); i++ )
        mc[i] = Point2f( mu[i].m10/mu[i].m00 , mu[i].m01/mu[i].m00 );

    /// Find the convex hull object for each contour
    vector<vector<Point> >hull( contours.size() );
    for( int i = 0; i < contours.size(); i++ )
        convexHull( Mat(contours[i]), hull[i], false );

    /// Draw contours
    Mat drawing = Mat::zeros( canny_output.size(), CV_8UC3 );
    for( int i = 0; i< contours.size(); i++ )
    {
        //Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
        Scalar color = Scalar(255,0,0);
        drawContours( drawing, contours, i, color, 2, 8, hierarchy, 0, Point() );
        //drawContours( frame, hull, i, color, 1, 8, hierarchy, 0, Point() );
        //circle( frame, mc[i], 4, color, -1, 8, 0 );

        /// Calculate the area with the moments 00 and compare with the result of the OpenCV function
        printf(" * Contour[%d] - Area (M_00) = %.2f - Area OpenCV: %.2f - Length: %.2f \n", i, mu[i].m00, contourArea(contours[i]), arcLength( contours[i], true ) );
        QString contour = QString(" * Contour") + QString::number(i) +  QString("- Area (M_00) = ") + QString::number(mu[i].m00) +
                           QString("- Area OpenCV: ") + QString::number(contourArea(contours[i]))  +
                               QString("- Length: "  + QString::number(arcLength( contours[i], true )));

        emit countors(contour);
    }

    processedFrame = drawing;
}
/**************** Contours and Convex Hulls ****************/

/**************** SURF Homography Feature Detector ****************/
void Player::SURFFeatureDetector()
{
    Mat src_gray;
    Mat canny_output;
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    //Hessian Thresholds
    const int thresh = 100;
    const int max_thresh = 255;
    RNG rng(12345);

    cvtColor(frame, src_gray, CV_BGR2GRAY );
    blur( src_gray, src_gray, Size(3,3) );

    SurfFeatureDetector detector( max_thresh );
    std::vector<KeyPoint> keypoints_1;

    detector.detect( src_gray, keypoints_1 );

    //-- Draw keypoints
    //Mat img_keypoints_1;

    drawKeypoints( src_gray, keypoints_1, src_gray, Scalar::all(-1), DrawMatchesFlags::DEFAULT );


    processedFrame = src_gray;
}
/**************** SURF Homography Feature Detector ****************/
