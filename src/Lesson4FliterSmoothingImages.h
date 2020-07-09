/*
 * Lesson4FliterSmoothingImages.h
 *
 *  Created on: Mar 28, 2019
 *      Author: ztftrue
 */

#ifndef SRC_LESSON4FLITERSMOOTHINGIMAGES_H_
#define SRC_LESSON4FLITERSMOOTHINGIMAGES_H_

#include <iostream>
#include <opencv4/opencv2/opencv.hpp>
#include <opencv4/opencv2/core.hpp>
#include <opencv4/opencv2/highgui.hpp>
#include <opencv4/opencv2/imgcodecs.hpp>
#include <opencv4/opencv2/imgproc.hpp>
using namespace cv;
/*
 * https://docs.opencv.org/4.0.1/dc/dd3/tutorial_gausian_median_blur_bilateral_filter.html
 */

class Lesson4FliterSmoothingImages {
private:

public:
	Lesson4FliterSmoothingImages();
	//滤波器
	int filter();
	virtual ~Lesson4FliterSmoothingImages();
};

#endif /* SRC_LESSON4FLITERSMOOTHINGIMAGES_H_ */
