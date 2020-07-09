/*
 * LessonA2FeaturesFramework.h
 *
 *  Created on: Mar 29, 2019
 *      Author: ztftrue
 */
#ifndef SRC_LESSONA2FEATURESFRAMEWORK_H_
#define SRC_LESSONA2FEATURESFRAMEWORK_H_

#include <iostream>
#include <opencv4/opencv2/opencv.hpp>
#include <opencv4/opencv2/core.hpp>
#include <opencv4/opencv2/highgui.hpp>
#include <opencv4/opencv2/imgcodecs.hpp>
#include <opencv4/opencv2/imgproc.hpp>
#include <opencv4/opencv2/features2d.hpp>
//#include <opencv4/opencv2/xfeatures2d.hpp>
#include <opencv4/opencv2/core/cvdef.h>
#include "stats.h" // Stats structure definition
#include "MyUtils.h" // Drawing and printing functions
#include "Tracker.h"

using namespace std;
using namespace cv;
//using namespace cv::xfeatures2d;

class LessonA2FeaturesFramework {
public:
	LessonA2FeaturesFramework();
	int AKAZEandORBplanar();
	int AKAZEmatching();
	virtual ~LessonA2FeaturesFramework();
protected:
	const float inlier_threshold = 2.5f; // Distance threshold to identify inliers with homography check
	const float nn_match_ratio = 0.8f;   // Nearest neighbor matching ratio
    MyUtils myUtils;

};

#endif /* SRC_LESSONA2FEATURESFRAMEWORK_H_ */
