#include <CMT.h>

//#define DEBUG_MODE

#ifdef DEBUG_MODE
#include <QDebug>
#endif


void num2str(char *str, int length, int num)
{
    for(int i = 0; i < length-1; i++)
    {
        str[length-i-2] = '0'+num%10;
        num /= 10;
    }
    str[length-1] = 0;
}

int main(int argc, char *argv[])
{
    cv::VideoCapture cap(atoi(argv[1]));

    CMT cmt;
    //cmt.estimateRotation = false;
    for(;;)
    {
        static int frame = 0;

        cv::Mat img;
        cap >> img;
        cv::Mat im_gray;
        cv::cvtColor(img, im_gray, CV_RGB2GRAY);

        if(frame < 10) {
            if(frame == 9)
                cmt.initialise(im_gray,
                               cv::Point2f(im_gray.cols / 4,im_gray.rows / 4),
                               cv::Point2f(3 * (im_gray.cols / 4),3 * (im_gray.rows / 4)));
        } else {
            cmt.processFrame(im_gray);
            for(int i = 0; i<cmt.trackedKeypoints.size(); i++)
                cv::circle(img, cmt.trackedKeypoints[i].first.pt, 3, cv::Scalar(255,255,255));
            cv::line(img, cmt.topLeft, cmt.topRight, cv::Scalar(255,255,255));
            cv::line(img, cmt.topRight, cmt.bottomRight, cv::Scalar(255,255,255));
            cv::line(img, cmt.bottomRight, cmt.bottomLeft, cv::Scalar(255,255,255));
            cv::line(img, cmt.bottomLeft, cmt.topLeft, cv::Scalar(255,255,255));

            #ifdef DEBUG_MODE
            qDebug() << "trackedKeypoints";
            for(int i = 0; i<cmt.trackedKeypoints.size(); i++)
                qDebug() << cmt.trackedKeypoints[i].first.pt.x << cmt.trackedKeypoints[i].first.pt.x << cmt.trackedKeypoints[i].second;
            qDebug() << "box";
            qDebug() << cmt.topLeft.x << cmt.topLeft.y;
            qDebug() << cmt.topRight.x << cmt.topRight.y;
            qDebug() << cmt.bottomRight.x << cmt.bottomRight.y;
            qDebug() << cmt.bottomLeft.x << cmt.bottomLeft.y;
            #endif
        }
        ++frame;



        imshow("frame", img);
        cv::waitKey(1);
    }
    return 0;
}
