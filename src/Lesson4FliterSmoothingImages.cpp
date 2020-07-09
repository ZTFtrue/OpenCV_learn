/*
 * Lesson4FliterSmoothingImages.cpp
 *
 *  Created on: Mar 28, 2019
 *      Author: ztftrue
 */

#include <Lesson4FliterSmoothingImages.h>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/mat.inl.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

Lesson4FliterSmoothingImages::Lesson4FliterSmoothingImages() {

}

int Lesson4FliterSmoothingImages::filter() {
	int MAX_KERNEL_LENGTH = 31;
	Mat dst;
	Mat src;
	int i = 3;
	/// 载入原图像
	src = imread("q.jpg", 1);
	imshow("src", src);
	dst = src.clone();
	blur(src, dst, Size(10, 10), Point(-1, -1));
	imshow("归一化块滤波器1", dst);
	for (int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2) { //归一化块滤波器
		//Size 内核大小   point锚点  如果是负值，取核的中心为锚点
		blur(src, dst, Size(i, i), Point(-1, -1));
	}
	imshow("归一化块滤波器", dst);

	for (int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2) {
		GaussianBlur(src, dst, Size(i, i), 0, 0);
	}
	imshow("高斯平滑", dst);
	// 使用中值平滑
	for (int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2) {
		medianBlur(src, dst, i);
	}
	imshow("中值平滑", dst);
	for (int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2) {
		bilateralFilter(src, dst, i, i * 2, i / 2);
	}
	imshow("双边平滑", dst);
	waitKey(0);
	return 0;
}

//归一化滤波器
void NormalizedBoxFilter(Mat src, int i = 3) {		//完全模糊
	Mat dst;
	blur(src, dst, Size(i, i), Point(-1, -1));
	imshow("归一化", dst);
}

//高斯滤波器
void GaussianFilter(Mat src, int i = 3) {		//较为完全模糊
	Mat dst;
	GaussianBlur(src, dst, Size(i, i), 0, 0);
	imshow("高斯", dst);
}

//中值滤波器
void MedianFilter(Mat src, int i = 3) {		//插线已不存在，好
	Mat dst;
	medianBlur(src, dst, i);
	imshow("中值", dst);
	imwrite("dst.jpg", dst);
}

//双边滤波
void BilateralFilter(Mat src, int i = 3) {		//好
	Mat dst;
	bilateralFilter(src, dst, i, i * 2, i / 2);
	imshow("双边", dst);
}
Lesson4FliterSmoothingImages::~Lesson4FliterSmoothingImages() {
}

