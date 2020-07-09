/*
 * AboutMat.cpp
 *
 *  Created on: Dec 5, 2018
 *      Author: ztftrue
 */

#include "Lesson1AboutMat.h"
using namespace cv;

Lesson1AboutMat::Lesson1AboutMat() {
}

Lesson1AboutMat::~Lesson1AboutMat() {
}

/*
 * 每个组成元素都有其自己的定义域，取决于其数据类型。如何存储一个元素决定了我们在其定义域上能够控
 *制的精度。最小的数据类型是 char ，占一个字节或者8位，可以是有符号型（0到255之间）或无符号型
 *（-127到+127之间）。尽管使用三个 char 型元素已经可以表示1600万种可能的颜色（使用RGB颜色空间），
 *但若使用float（4字节，32位）或double（8字节，64位）则能给出更加精细的颜色分辨能力。但同时也要
 *切记增加元素的尺寸也会增加了图像所占的内存空间。
 */
void Lesson1AboutMat::vec() {
//	如果多通道图像,如 RGB 彩色图像,需要用三个通道来表示。在这种情况
//	下,如果依然将图像视作一个二维矩阵,那么矩阵的元素不再是基本的数据类型。
//	26OpenCV 中有模板类 Vec,可以表示一个向量。OpenCV 中使用 Vec 类预定义了一
//	些小向量,可以将之用于矩阵元素的表达。

//	例如 8U 类型的 RGB 彩色图像可以使用 Vec3b,3 通道 float 类型的矩阵可以
//	使用 Vec3f。
//	对于 Vec 对象,可以使用[]符号如操作数组般读写其元素,如:
	Vec3b color; //用 color 变量描述一种 RGB 颜色
	color[0] = 255; //B 分量
	color[1] = 0; //G 分量
	color[2] = 0; //R 分量
	Mat A = imread("b.jpg");
	imshow("A", A);
	Mat B = A.row(10); //选择A的第十行
	imshow("B", B*2);
//	 B=A.col(2)*2;//选择A的第十列
	Mat C = A(Range::all(), Range(1, 3)); //所有行，一到三列
//	用 Range 选择多行或多列
//A.t();
	waitKey(0);
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
}
/*
 * 打印图像和图像基础知识
 */
void Lesson1AboutMat::printMat() {
	/*
	 * OpenCV函数的输出图像分配是自动的（除非另有说明）。
	 * 您不需要考虑使用OpenCVs C ++接口进行内存管理。
	 * 赋值运算符和复制构造函数仅复制标题。
	 * 可以使用cv::Mat::clone()和cv::Mat::copyTo()函数复制图像的基础矩阵。
	 */
	// https://docs.opencv.org/master/d6/d6d/tutorial_mat_the_basic_image_container.html
	// OpenCV uses a reference counting system
	cv::Mat C = cv::imread("assets/a.jpg", IMREAD_UNCHANGED);
	Mat B(C); //只拷贝信息头和矩阵指针 使用复制构造函数
	B = C;  //赋值运算符
	B = cv::imread("assets/a.jpg", IMREAD_UNCHANGED);
	Mat F = B.clone();
	Mat G;
	F.copyTo(G); // 复制图像,改变F或者G就不会影响A
	cout << "C = " << endl << " " << C << endl << endl;
	cout << "R (c) = " << endl << C << endl << endl;
	//二维点
	Point2f P(5, 1);
	cout << "Point (2D) = " << P << endl << endl;
	//三维点
	Point3f P3f(2, 6, 6);
	cout << "Point(3D)= " << P3f << endl;
	//基于cv::Mat的std::vector
	vector<float> v;
	v.push_back((float) CV_PI);
	v.push_back(2);
	v.push_back(3.01f);
	cout << "Vector of floats via Mat = " << Mat(v) << endl << endl;
	Mat H(C, Rect(10, 10, 100, 100)); //使用矩形
	Mat E = C(Range::all(), Range(1, 3)); //使用行和列边界
	// 显式创建Mat对象
	Mat M(2, 2, CV_8UC3, Scalar(0, 0, 255));
	cout << "M = " << endl << " " << M << endl << endl;
	int sz[3] = { 2, 2, 2 };
	Mat L(3, sz, CV_8UC(1), Scalar::all(0));
}
/*
 * 操作图像
 * waitKey  等待按键
 * Canny 寻找轮廓
 */
void Lesson1AboutMat::operatingMat() {
	Mat A, B, C;
	A = imread("assets/a.jpg", IMREAD_COLOR);
	namedWindow("A原图");
//	waitKey(1000);
	imshow("A原图", A);
	Mat H(A, Rect(200, 100, 200, 200)); //以左上角开始：左，上，右，下
	imshow("A裁剪", H);
//	Mat I = A(Range::all(), Range(0,70)); // using row and column boundaries
	Mat I = A(Range(0, 600), Range(0, 70)); // using row and column boundaries行，列
	imshow("a", I);
	cout << "I message\n" << I.rows << endl << I.flags << endl << I.cols
			<< endl;
	int thickness = 2;    //线粗
	int lineType = 8;    //此线为8联通 (lineType = 8)
	Point3d pEnd(100, 100, 100);
	cout << "" << endl;
	Point2f P(5, 1);
//	cout << "Point" << P << endl << pEnd << endl;
	imshow("A+A", A + A);
	imshow("A*double", A * 0.5);

	/*第一行代码创建一个行数(高度)为 3,列数(宽度)为 2 的图像,图像元
	 素是 8 位无符号整数类型,且有三个通道。图像的所有像素值被初始化为(0, 0,
	 255)。由于 OpenCV 中默认的颜色顺序为 BGR,因此这是一个全红色的图像。*/
	waitKey(0);
	Mat M(20, 20, CV_8UC3, Scalar(0, 0, 255)); //Scalar 像素颜色
	Mat colorim(600, 800, CV_8UC3);
	M.at<int>(10, 10) = 128;
	MatIterator_<Vec3b> colorit, colorend;
	//进行 Canny 操作,并将结果存于 result
	Mat result;
	Canny(A + A + A, result, 50, 150); //获取轮廓
	//保存结果
	imwrite("output/a.jpg", result);
	for (colorit = colorim.begin<Vec3b>(), colorend = colorim.end<Vec3b>();
			colorit != colorend; ++colorit) {
		(*colorit)[0] = rand() % 255; //Blue
		(*colorit)[1] = rand() % 255; //Green
		(*colorit)[2] = rand() % 255; //Red
	}
	imshow("c", M);
	imshow("c1", colorim);
//	imshow("对角线",A.diag(0));
	cout << "M = " << endl << " " << M << endl << endl;
//	int sz[3] = { 2, 2, 2 };
//	Mat L(3, sz, CV_8UC(1), Scalar::all(0));
}
/*
 * 遍历
 */
void Lesson1AboutMat::iteratorMat() {
	/* 如果你熟悉 C++的 STL 库,那一定了解迭代器(iterator)的使用。迭代器可
	 * 以方便地遍历所有元素。Mat 也增加了迭代器的支持,以便于矩阵元素的遍历。
	 * 下面的例程功能跟上一节的例程类似,但是由于使用了迭代器,而不是使用行数
	 * 和列数来遍历,所以这儿没有了 i 和 j 变量,图像的像素值设置为一个随机数。*/
	Mat B = imread("assets/a.jpg");
	//遍历所有像素,并设置像素值
	MatIterator_<Vec3b> colorit, colorend;
	for (colorit = B.begin<Vec3b>(), B.end<Vec3b>(); colorit != colorend;
			++colorit) {
		(*colorit)[0] = rand() % 255; //Blue  rand()产生随机数
		(*colorit)[1] = rand() % 255; //Green
		(*colorit)[2] = rand() % 255; //Red
	}

	cv::Mat A = cv::imread("assets/a.jpg", 3);
	B = imread("assets/b.jpg");
	uchar value = A.at < uchar > (1, 2); //获取第一行第二列的值
	Vec3i v3f = A.at < Vec3i > (2, 3);
	cout << value << endl;
	cout << v3f << endl;
	value = 128;
	imshow("A+B", A);
	uchar value2 = A.at < uchar > (1, 2); //获取第一行第二列的值
	waitKey(0);
	cout << "!!!Hello World!!!" << value2 << endl; // prints !!!Hello World!!!

	Mat M(600, 800, CV_8UC1);
	//在变量声明时指定矩阵元素类型
	Mat_ < uchar > M1 = (Mat_<uchar> &) M;
	for (int i = 0; i < M1.rows; ++i) {
		//不需指定元素类型,语句简洁
		uchar *p = M1.ptr(i);
		for (int j = 0; j < M1.cols; ++j) {
			double d1 = (double) ((i + j) % 255);
			//直接使用 Matlab 风格的矩阵元素读写,简洁
			M1(i, j) = d1;
			double d2 = M1(i, j);
		}
	}
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
}


