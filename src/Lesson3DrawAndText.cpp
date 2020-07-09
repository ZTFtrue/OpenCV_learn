//
// Created by ztftrue on 17-11-7.
//

#include <Lesson3DrawAndText.h>

void Lesson3DrawAndText::drawGraph() {
	Point pt; //点
	pt.x = 0;
	pt.y = 0;
	Point point = Point(1000, 1000);
	//Scalar(a,b,c);表示具有4个元素的数组 ，第四个参数如果不用则无需定义。
	/// 窗口名字
	char atom_window[] = "Drawing 1: Atom";
	char rook_window[] = "Drawing 2: Rook";
	int w = 1000;
	/// 创建空全黑像素的空图像
	Mat atom_image = Mat(w, w, CV_8UC3);
	Mat rook_image = Mat(w, w, CV_8UC3);
	RNG rng(0xFFFFFFFF);    //随机数发生器
	// 创建一个名为 "游戏原画"窗口
	// https://docs.opencv.org/master/d7/dfc/group__highgui.html#ga5afdf8410934fd099df85c75b2e0888b
	namedWindow("游戏原画", WINDOW_AUTOSIZE);
	/// 初始化一个0矩阵
	Mat image = Mat(w, w, CV_8UC3);
	Point pt2 = Point(100, 500);
	putText(image, "Testing text rendering", pt2, rng.uniform(0, 8),
			rng.uniform(0, 100) * 0.05 + 0.1, Scalar(0, 255, 255),
			rng.uniform(1, 10), 8);
	/// 把它会知道一个窗口中
	imshow("window_name", image);
	// 在窗口中显示游戏原画

	// 等待6000 ms后窗口自动关闭
	waitKey(6000);
	Mat img = imread("qw.jpg");
	imshow("window_name", img);
	waitKey(6000);
	double alpha = 0.5;
	int beta = 0.5;
	string source_window = "Source image";
	string equalized_window = "Equalized Image";
	Mat new_image = Mat(img.size(), img.type());
	Mat dst;
	// Converts an image from one color space to another.
	cvtColor(img, img, COLOR_BGR2GRAY);    /// 转为灰度图
	equalizeHist(img, dst);    // 应用直方图均衡化

	namedWindow(source_window, WINDOW_AUTOSIZE);    //显示通知
	namedWindow(equalized_window, WINDOW_AUTOSIZE);

	imshow(source_window, img);
	imshow(equalized_window, dst);
	waitKey(0);
	//	image.convertTo(new_image, -1, alpha, beta);改变图片的亮度和对比度
	for (int y = 0; y < img.rows; y++) {
		for (int x = 0; x < img.cols; x++) {
			for (int c = 0; c < 3; c++) {
				new_image.at<Vec3b>(y, x)[c] = saturate_cast<uchar>(
						alpha * (img.at<Vec3b>(y, x)[c]) + beta);
			}
		}
	}

	imshow("window_name2", img);
	waitKey(6000);
	//
	//    imshow("t",img);
	//    waitKey(6000);
}
void Lesson3DrawAndText::MyLine(Mat img, Point start, Point end) {
	int thickness = 2;    //线粗
	int lineType = 8;    //此线为8联通 (lineType = 8)
	line(img, start, end, Scalar(20, 0, 10), thickness, lineType);
	rectangle(img, Point(0, 7 * 500 / 8.0), Point(500, 500),
			Scalar(0, 255, 255), -1, 8);
}

void Lesson3DrawAndText::myEllipse(Mat img, double angle) {
	int thicknees = 2;
	int lineType = 8;
	Vec3i vec;
	vec[1] = 100;
	vec[0] = 100;
	vec[2] = 100;

	//椭圆画到img上，中心点，大小位于矩形(高，宽),旋转角度为angle, 椭圆扩展的弧度为0～,360度（椭圆的完整性），颜色为Scalar，线粗为
	ellipse(img, Point(w / 2, h / 2), Size(w / 4.0, w / 16.0), angle, 0, 360,
			vec /*Scalar( 0, 0, 255 )*/, thicknees, lineType);
}

void Lesson3DrawAndText::MyCircle(Mat img, Point center) {
	int thickness = -1;
	int lineType = 8;
	circle(img, center, h / 10.0, Scalar(0, 0, 255), thickness, lineType);
}
//在 image 上绘制文字 “Testing text rendering” 。
//文字的左下角将用点 org 指定。
//字体参数是用一个在 [0, 8> 之间的整数来定义。
//字体的缩放比例是用表达式 rng.uniform(0, 100)x0.05 + 0.1 指定(表示它的范围是 [0.1, 5.1>)。
//字体的颜色是随机的 (记为 randomColor(rng))。
//字体的粗细范围是从 1 到 10, 表示为 rng.uniform(1,10) 。
int Lesson3DrawAndText::Displaying_Big_End(Mat image, String window_name,
		RNG rng) {
	Size textsize = getTextSize("OpenCV forever!", FONT_HERSHEY_COMPLEX, 3, 5,
			0);
	Point org((w - textsize.width) / 2, (h - textsize.height) / 2);
	int lineType = 8;
	Mat image2;
	for (int i = 0; i < 255; i += 2) {
		image2 = image - Scalar::all(i);
		putText(image2, "OpenCV forever!", org, FONT_HERSHEY_COMPLEX, 3,
				Scalar(i, i, 255), 5, lineType);
		imshow(window_name, image2);
		waitKey(0);
	}
	return 0;
}

//调用画图方法
void Lesson3DrawAndText::Draw() {
	Point pt; //画笔
	pt.x = 10;
	pt.y = 10;
	Scalar(100, 255, 255);
	Vec3i vec;
	vec[1] = 100;
	Mat img = imread("a.jpg");
	w = img.cols;
	h = img.rows;
	Point pt2 = Point(w / 2, h / 2);
	myEllipse(img, 0);
	MyCircle(img, pt2);
	MyPolygon(img);
	imshow("椭圆", img);
	waitKey(0);
}

void Lesson3DrawAndText::MyPolygon(Mat img) {
	int lineType = 8;
	/** 创建一些点 */
	Point rook_points[1][20];
	rook_points[0][0] = Point(w / 4.0, 7 * w / 8.0);
	rook_points[0][1] = Point(3 * w / 4.0, 7 * w / 8.0);
	rook_points[0][2] = Point(3 * w / 4.0, 13 * w / 16.0);
	rook_points[0][3] = Point(11 * w / 16.0, 13 * w / 16.0);
	rook_points[0][4] = Point(19 * w / 32.0, 3 * w / 8.0);
	rook_points[0][5] = Point(3 * w / 4.0, 3 * w / 8.0);
	rook_points[0][6] = Point(3 * w / 4.0, w / 8.0);
	rook_points[0][7] = Point(26 * w / 40.0, w / 8.0);
	rook_points[0][8] = Point(26 * w / 40.0, w / 4.0);
	rook_points[0][9] = Point(22 * w / 40.0, w / 4.0);
	rook_points[0][10] = Point(22 * w / 40.0, w / 8.0);
	rook_points[0][11] = Point(18 * w / 40.0, w / 8.0);
	rook_points[0][12] = Point(18 * w / 40.0, w / 4.0);
	rook_points[0][13] = Point(14 * w / 40.0, w / 4.0);
	rook_points[0][14] = Point(14 * w / 40.0, w / 8.0);
	rook_points[0][15] = Point(w / 4.0, w / 8.0);
	rook_points[0][16] = Point(w / 4.0, 3 * w / 8.0);
	rook_points[0][17] = Point(13 * w / 32.0, 3 * w / 8.0);
	rook_points[0][18] = Point(5 * w / 16.0, 13 * w / 16.0);
	rook_points[0][19] = Point(w / 4.0, 13 * w / 16.0);
	const Point *ppt[1] = { rook_points[0] };
	int npt[] = { 20 };
	fillPoly(img, ppt, npt, 1, Scalar(255, 255, 255), lineType);
}
