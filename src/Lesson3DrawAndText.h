//
// Created by ztftrue on 17-11-7.
//

#ifndef OPENCV_DRAW_H
#define OPENCV_DRAW_H

#include <iostream>
#include <opencv4/opencv2/opencv.hpp>
#include <opencv4/opencv2/core.hpp>
#include <opencv4/opencv2/highgui.hpp>
#include <opencv4/opencv2/imgcodecs.hpp>
#include <opencv4/opencv2/imgproc.hpp>

using namespace cv;
using namespace std;

class Lesson3DrawAndText {
private:
	int w;
	int h;
public:
	void drawGraph();

	void MyLine(Mat img, Point start, Point end);

	//画椭圆
	void myEllipse(Mat img, double angle);

//画圆
	void MyCircle(Mat img, Point center);
//绘制多边形
	void MyPolygon(Mat img) ;

	void Draw();
	int Displaying_Big_End(Mat image, String window_name, RNG rng) ;

};

#endif //OPENCV_DRAW_H
