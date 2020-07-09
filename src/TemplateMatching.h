/*
 * TemplateMatching.h
 *
 *  Created on: Mar 30, 2019
 *      Author: ztftrue
 */

#ifndef SRC_TEMPLATEMATCHING_H_
#define SRC_TEMPLATEMATCHING_H_
#include <iostream>
#include <opencv4/opencv2/opencv.hpp>
#include <opencv4/opencv2/core.hpp>
#include <opencv4/opencv2/highgui.hpp>
#include <opencv4/opencv2/imgcodecs.hpp>
#include <opencv4/opencv2/imgproc.hpp>
using namespace cv;


class TemplateMatching {
public:
	TemplateMatching();
	int matching();
	virtual ~TemplateMatching();
protected:


};

#endif /* SRC_TEMPLATEMATCHING_H_ */
