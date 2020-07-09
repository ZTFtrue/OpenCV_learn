/*
 * LessonAFeaturesFramework.h
 *
 *  Created on: Mar 28, 2019
 *      Author: ztftrue
 */
#ifndef LESSONAFEATURESFRAMEWORK_H_
#define LESSONAFEATURESFRAMEWORK_H_

#include <iostream>
#include <opencv4/opencv2/opencv.hpp>
#include <opencv4/opencv2/core.hpp>
#include <opencv4/opencv2/highgui.hpp>
#include <opencv4/opencv2/imgcodecs.hpp>
#include <opencv4/opencv2/imgproc.hpp>
#include <opencv4/opencv2/features2d.hpp>
#include <opencv4/opencv2/xfeatures2d.hpp>
#include <opencv4/opencv2/core/cvdef.h>

using namespace std;
using namespace cv;
//using namespace cv::xfeatures2d;

class LessonAFeaturesFramework {
public:
	LessonAFeaturesFramework();
	int harrisCornerDetector();
	int shiTomasiCornerDetector();
	int yourOwnCornerDetector();
	int detectingCornersLocationsInSubpixels();
	int features2dDetection();
	int featureMatchingFLANN();
	int feature2DHomographyFindObject();
	/*
	 * 检测平面物体
	 */
	int detectionPlanarObjects();
	virtual ~LessonAFeaturesFramework();
};

#endif
