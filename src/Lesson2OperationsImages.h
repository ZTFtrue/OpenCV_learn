/*
 * Lesson2OperationsImages.h
 *
 *  Created on: Mar 27, 2019
 *      Author: ztftrue
 */

#ifndef LESSON2OPERATIONSIMAGES_H_
#define LESSON2OPERATIONSIMAGES_H_

#include <iostream>

#include <opencv4/opencv2/opencv.hpp>
#include <opencv4/opencv2/core.hpp>
#include <opencv4/opencv2/highgui.hpp>
#include <opencv4/opencv2/imgcodecs.hpp>
#include <opencv4/opencv2/imgcodecs.hpp>
#include <opencv4/opencv2/imgproc.hpp>
#include <math.h>
using namespace cv;
using namespace std;
class Lesson2OperationsImages {
public:
	Lesson2OperationsImages();
	// 矩阵掩码  变得更锐利
	void sharpen();
	/*应用这样的滤波器在图像处理中是如此常见，
	 * 以至于在OpenCV中存在将负责应用掩模的功能
	 * （在某些地方也称为内核）。
	 * 为此，您首先需要定义一个包含掩码的对象：
	 *   Mat kernel = (Mat_<char>(3,3) <<  0, -1,  0,
	 -1,  5, -1,
	 0, -1,  0);
	 */
	void myFilter2d();

	/*
	 * 为了获得像素强度值，您必须知道图像的类型和通道的数量。以下是单通道灰度图像（类型8UC1）和像素坐标x和y的示例：
	 */
	void acessingPixelIntensity();
	int addBlendingImag();
	int changingBrightness();
	int discreteFourierTransform();
	virtual ~Lesson2OperationsImages();
};

#endif /* LESSON2OPERATIONSIMAGES_H_ */
