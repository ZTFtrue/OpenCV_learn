/*
 * 图像的膨胀与腐蚀
 */

#ifndef OPENCV_ERODINGDILATING_H
#define OPENCV_ERODINGDILATING_H

#include <iostream>
#include <opencv4/opencv2/opencv.hpp>
#include <opencv4/opencv2/core.hpp>
#include <opencv4/opencv2/highgui.hpp>
#include <opencv4/opencv2/imgcodecs.hpp>
#include <opencv4/opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

class ErodingDilating {
private:
    Mat src;
    Mat erosion_dst, dilation_dst;
    int erosion_elem = 0;
    int erosion_size = 0;
    int dilation_elem = 0;
    int dilation_size = 0;
    int const max_elem = 2;
    int const max_kernel_size = 21;
public:
    /*
     *  腐蚀操作
     */
    void Erosion(int, void *) {
        int erosion_type = 0;
        if (erosion_elem == 0) {
            erosion_type = MORPH_RECT;
        } else if (erosion_elem == 1) {
            erosion_type = MORPH_CROSS;
        } else if (erosion_elem == 2) {
            erosion_type = MORPH_ELLIPSE;
        }

        Mat element = getStructuringElement(erosion_type,
                                            Size(2 * erosion_size + 1, 2 * erosion_size + 1),
                                            Point(erosion_size, erosion_size));

        // 腐蚀操作
        erode(src, erosion_dst, element);
        imshow("Erosion Demo", erosion_dst);
    }

    //膨胀操作
    void Dilation(int, void *) {
        int dilation_type = 0;
        if (dilation_elem == 0) {
            dilation_type = MORPH_RECT;
        } else if (dilation_elem == 1) {
            dilation_type = MORPH_CROSS;
        } else if (dilation_elem == 2) {
            dilation_type = MORPH_ELLIPSE;
        }

        Mat element = getStructuringElement(dilation_type,
                                            Size(2 * dilation_size + 1, 2 * dilation_size + 1),
                                            Point(dilation_size, dilation_size));
        //膨胀操作
        dilate(src, dilation_dst, element);
        imshow("Dilation Demo", dilation_dst);
    }

    //开运算是通过先对图像腐蚀再膨胀实现的
    //能够排除小团块物体(假设物体较背景明亮)
    void opening() {

    }

    //闭运算是通过先对图像膨胀再腐蚀实现的。
    //能够排除小型黑洞(黑色区域)。
    void closing() {

    }

    //形态梯度(Morphological Gradient):膨胀图与腐蚀图之差
    //能够保留物体的边缘轮廓，如下所示:
    void morphological() {

    }
    void erodingAndDilating() {
//    	(const String& trackbarname, const String& winname,
//    	                              int* value, int count,
//    	                              TrackbarCallback onChange = 0,
//    	                              void* userdata = 0);
        /// 创建显示窗口
        namedWindow("Erosion Demo", WINDOW_AUTOSIZE);
        namedWindow("Dilation Demo", WINDOW_AUTOSIZE);
        moveWindow("Dilation Demo", src.cols, 0);

//        /// 创建腐蚀 Trackbar
//        createTrackbar("Element:\n 0: Rect \n 1: Cross \n 2: Ellipse",
//                       "Erosion Demo", &erosion_elem, max_elem, Erosion);
//
//        createTrackbar("Kernel size:\n 2n +1", "Erosion Demo", &erosion_size,
//                       max_kernel_size, Erosion);
//
//        /// 创建膨胀 Trackbar
//        createTrackbar("Element:\n 0: Rect \n 1: Cross \n 2: Ellipse",
//                       "Dilation Demo", &dilation_elem, max_elem, Dilation);
//
//        createTrackbar("Kernel size:\n 2n +1", "Dilation Demo", &dilation_size,
//                       max_kernel_size, Dilation);

        /// Default start
        Erosion(0, 0);
        Dilation(0, 0);

        waitKey(0);
    }
};


#endif //OPENCV_ERODINGDILATING_H
