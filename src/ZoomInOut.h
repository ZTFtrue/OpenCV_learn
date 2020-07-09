/*
 * 缩放图片
 */

#ifndef OPENCV_ZOOMINOUT_H
#define OPENCV_ZOOMINOUT_H

#include <opencv4/opencv2/opencv.hpp>
#include <opencv4/opencv2/core.hpp>
#include <opencv4/opencv2/highgui.hpp>
#include <opencv4/opencv2/imgcodecs.hpp>
#include <opencv4/opencv2/imgproc.hpp>
using namespace cv;

class ZoomInOut {
private:
    Mat dst, tmp;
    const char *window_name = "Pyramids Demo";
    int a;
public:
    void Method(Mat src);

    ZoomInOut(int a);

    ~ZoomInOut();

};


#endif //OPENCV_ZOOMINOUT_H
