/*
 * AboutMat.h
 *
 *  Created on: Dec 5, 2018
 *      Author: ztftrue
 *      关于Mat，opencv Mat 的介绍，
 */

#ifndef LESSON1ABOUTMAT_H_
#define LESSON1ABOUTMAT_H_

#include <iostream>
#include <opencv4/opencv2/opencv.hpp>
#include <opencv4/opencv2/core.hpp>
#include <opencv4/opencv2/highgui.hpp>
#include <opencv4/opencv2/imgcodecs.hpp>
#include <opencv4/opencv2/imgproc.hpp>

using namespace std;
using namespace cv;
class Lesson1AboutMat {
public:
	Lesson1AboutMat();
	void vec();
	void printMat();
	void operatingMat();
	void iteratorMat();
	virtual ~Lesson1AboutMat();
};
#endif /* LESSON1ABOUTMAT_H_ */
