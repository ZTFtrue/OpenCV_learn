/*
 * MyUtils.h
 *
 *  Created on: Mar 29, 2019
 *      Author: ztftrue
 */

#ifndef SRC_MYUTILS_H_
#define SRC_MYUTILS_H_
#include <opencv4/opencv2/opencv.hpp>
#include <opencv4/opencv2/opencv.hpp>
#include <opencv4/opencv2/core.hpp>
#include <opencv4/opencv2/imgcodecs.hpp>
#include <opencv4/opencv2/imgproc.hpp>
#include <opencv4/opencv2/calib3d.hpp>
#include <iostream>
#include <iomanip>
#include <vector>
#include "stats.h"

using namespace std;
using namespace cv;

class MyUtils {
public:
	MyUtils();
	void drawBoundingBox(Mat image, vector<Point2f> bb);
	void drawStatistics(Mat image, const Stats& stats);
	void printStatistics(string name, Stats stats);
	vector<Point2f> Points(vector<KeyPoint> keypoints);
	virtual ~MyUtils();
};

#endif /* SRC_MYUTILS_H_ */
