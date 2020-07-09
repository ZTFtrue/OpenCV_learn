//============================================================================
// Name        : openCamera.cpp
// Author      : ztftrue
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <opencv4/opencv2/opencv.hpp>
#include <opencv4/opencv2/core.hpp>
#include <opencv4/opencv2/highgui.hpp>
#include <opencv4/opencv2/imgcodecs.hpp>
#include <opencv4/opencv2/imgproc.hpp>
#include <opencv4/opencv2/videoio.hpp>
#include <iostream>
using namespace std;
using namespace cv;
int openCamera() {
	//打开第一个摄像头
	VideoCapture cap(0);
	//打开视频文件
//	VideoCapture cap("video.short.raw.avi");
	//检查是否成功打开
	if (!cap.isOpened()) {
		cerr << "Can not open a camera or file." << endl;
		return -1;
	}
	Mat edges;
	//创建窗口
	namedWindow("edges", 1);
	for (;;) {
		Mat frame;
		//从 cap 中读一帧,存到 frame
		cap >> frame;
		//如果未读到图像
		if (frame.empty())
			break;
		//将读到的图像转为灰度图
		cvtColor(frame, edges, COLOR_BGR2GRAY);
		//进行边缘提取操作
		Canny(edges, edges, 100, 80, 5);
		//显示结果
		imshow("edges", edges);
		//等待 30 秒,如果按键则推出循环
		waitKey(2);
	}
	//退出时会自动释放 cap 中占用资源
	return 0;
}
void readWriteVideo() {	//写入摄像头或视频文件
	//打开第一个摄像头
	VideoCapture cap(0);
	//打开视频文件
//	VideoCapture cap("v.dv");
	//检查cap是否打开
	if (!cap.isOpened()) {
		cerr << "Can not open file\n" << endl;
		Mat edges;
		namedWindow("edges", 1);
		for (;;) {
			Mat frame;
			cap >> frame;	//重cap中读取一张，存到frame
			//如果未读到图像
			cvtColor(frame, edges, COLOR_BGR2BGRA);
			Canny(edges, edges, 0, 30, 30);
			imshow("edges", edges);
			if (waitKey(30) >= 0) {
				break;
			}
		}
	}
	//定义视频的宽度和高度
	Size s(300, 240);
	//创建writer,并指定FOURCC及FPS等参数
	VideoWriter videoWriter = VideoWriter("myvideo.avi",
			VideoWriter::fourcc('M', 'J', 'P', 'G'), 25, s);
	//检查是否创建成功
	if (!videoWriter.isOpened()) {
		cerr << "Can not create video file.\n" << endl;
		return;
	}
	Mat frame(s, CV_8UC3);			//视频帧
	for (int i = 0; i < 100; i++) {
		//将图像设置黑色
		frame = Scalar::all(0);
		char text[128];
		snprintf(text, sizeof(text), "%d", i);
		//将数字画到画面上
		putText(frame, text, Point(s.width / 3, s.height / 3),
				FONT_HERSHEY_SCRIPT_SIMPLEX, 3, Scalar(0, 0, 255), 3, 8);
		videoWriter << frame;
	}
}
