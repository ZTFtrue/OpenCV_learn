/*
 * Lesson2OperationsImages.cpp
 * 图像处理，xml、yaml文件
 *  Created on: Mar 27, 2019
 *      Author: ztftrue
 */

#include "Lesson2OperationsImages.h"

Lesson2OperationsImages::Lesson2OperationsImages() {

}

void Lesson2OperationsImages::sharpen() {
	const Mat& myImage = imread("a.jpg", cv::IMREAD_UNCHANGED);
	Mat Result;
	CV_Assert(myImage.depth() == CV_8U);  // accept only uchar images
	const int nChannels = myImage.channels();  // 元素的总数  rgb
	Result.create(myImage.size(), myImage.type());
	for (int j = 1; j < myImage.rows - 1; ++j) {
		const uchar* previous = myImage.ptr<uchar>(j - 1);
		const uchar* current = myImage.ptr<uchar>(j);
		const uchar* next = myImage.ptr<uchar>(j + 1);
		uchar* output = Result.ptr<uchar>(j);
		for (int i = nChannels; i < nChannels * (myImage.cols - 1); ++i) {
			*output++ = saturate_cast<uchar>(
					5 * current[i] - current[i - nChannels]
							- current[i + nChannels] - previous[i] - next[i]);
		}
	}
	Result.row(0).setTo(Scalar(0));
	Result.row(Result.rows - 1).setTo(Scalar(0));
	Result.col(0).setTo(Scalar(0));
	Result.col(Result.cols - 1).setTo(Scalar(0));
	imshow("result", Result);
}

void Lesson2OperationsImages::myFilter2d() {
	//  filter2D( src, dst1, src.depth(), kernel );
	const Mat& src = imread("a.jpg", cv::IMREAD_UNCHANGED);
	imshow("src", src);
	Mat dist;
	// 用内核卷积图像
	filter2D(src, dist, src.depth(), 5);
	imshow("filter2D", dist);
}

/*
 * 为了获得像素强度值，您必须知道图像的类型和通道的数量。
 * 请注意x和y的顺序。由于在OpenCV中图像由与矩阵相同的结构表示
 */
void Lesson2OperationsImages::acessingPixelIntensity() {
	Mat dst;
	Mat img = imread("a.jpg", cv::IMREAD_UNCHANGED); // Loads the test image
	int x, y;
	// 以下是单通道灰度图像（类型8UC1）和像素坐标x和y的示例：
	Scalar intensity = img.at<uchar>(y, x);
	// 仅限C++
	Scalar intensityC1 = img.at<uchar>(Point(x, y));
	intensity.val[0]; // 包含0到255之间的值

	uchar blue = intensity.val[0];
	uchar green = intensity.val[1];
	uchar red = intensity.val[2];
	// 仅限c++
	Vec3f intensity2 = img.at<Vec3f>(y, x);
	float blue1 = intensity.val[0];
	float green1 = intensity.val[1];
	float red1 = intensity.val[2];

	//The same method can be used to change pixel intensities:
	img.at<uchar>(y, x) = 128;

	// 仅限c++
	Point2f point = img.at<Point2f>(x, 0);
	// 8UC1 to 32FC1:
	img.convertTo(dst, CV_32F);
	// Sobel算子结合了高斯平滑和微分，因此结果或多或少地抵抗噪声。
	Sobel(img, dst, CV_32F, 1, 0);
	double minVal, maxVal;
	minMaxLoc(img, &minVal, &maxVal); //find minimum and maximum intensities
}
/*
 * 图像相加
 */
int Lesson2OperationsImages::addBlendingImag() {
	double alpha = 0.5;
	double beta;
	double input;
	Mat src1, src2, dst;
	cout << " Simple Linear Blender " << endl;
	cout << "-----------------------" << endl;
	cout << "* Enter alpha [0.0-1.0]: ";
	cin >> input;
	// We use the alpha provided by the user if it is between 0 and 1
	if (input >= 0 && input <= 1) {
		alpha = input;
	}
	src1 = imread("a.jpg");
	src2 = imread("a.jpg");
	if (src1.empty()) {
		cout << "Error loading src1" << endl;
		return -1;
	}
	if (src2.empty()) {
		cout << "Error loading src2" << endl;
		return -1;
	}
	beta = (1.0 - alpha);
	// Calculates the weighted sum of two arrays.
	// dst(I)=saturate(src1(I)∗alpha+src2(I)∗beta+gamma)
	addWeighted(src1, alpha, src2, beta, 0.0, dst);
	imshow("Linear Blend", dst);
	waitKey(0);
	return 0;
}
//Brightness and contrast adjustments
// g(x)=αf(x)+β   α 对比度  β 亮度
int Lesson2OperationsImages::changingBrightness() {
//	CommandLineParser parser(argc, argv,
//			"{@input | ../data/lena.jpg | input image}");
//	Mat image = imread(parser.get<String>("@input"));
	Mat image = imread("a.jpg");
	if (image.empty()) {
		cout << "Could not open or find the image!\n" << endl;
		return -1;
	}
	Mat new_image = Mat(image.size(), image.type());
	double alpha = 1.0; /*< Simple contrast control */
	int beta = 0; /*< Simple brightness control */
	cout << " Basic Linear Transforms " << endl;
	cout << "-------------------------" << endl;
	cout << "* Enter the alpha value [1.0-3.0]对比度: ";
	cin >> alpha;
	cout << "* Enter the beta value [0-100]亮度: ";
	cin >> beta;
	//现在，为了执行操作g（i，j）=α⋅f（i，j）+β，
	//我们将访问图像中的每个像素。由于我们使用BGR图像进行操作，
	//因此每个像素（B，G和R）将有三个值，因此我们也将单独访问它们。
	for (int y = 0; y < image.rows; y++) {
		for (int x = 0; x < image.cols; x++) {
			for (int c = 0; c < image.channels(); c++) {
				new_image.at<Vec3b>(y, x)[c] = saturate_cast<uchar>(
						alpha * image.at<Vec3b>(y, x)[c] + beta);
			}
		}
	}
	imshow("Original Image", image);
	imshow("New Image", new_image);
	// 图像校正
	// https://docs.opencv.org/4.0.1/d3/dc1/tutorial_basic_linear_transform.html
	Mat lookUpTable(1, 256, CV_8U);
	uchar* p = lookUpTable.ptr();
	double gamma_ = 10;
	for (int i = 0; i < 256; ++i)
		p[i] = saturate_cast<uchar>(pow(i / 255.0, gamma_) * 255.0);
	Mat res = image.clone();
	LUT(image, lookUpTable, res);
	imshow("res", res);
	return 0;
}

/*
 * https://docs.opencv.org/4.0.1/d8/d01/tutorial_discrete_fourier_transform.html
 * 离散傅立叶变换
 * dft();
 * 傅里叶变换将图像分解为其正弦和余弦分量。
 * 换句话说，它将图像从其空间域变换到其频域。
 * 这个想法是任何函数可以用无限正弦和余弦函数的总和精确地近似。
 * 傅里叶变换是一种如何做到这一点的方法。数学上二维图像傅里叶变换是：
 */
int Lesson2OperationsImages::discreteFourierTransform() {
//	const char* filename = argc >= 2 ? argv[1] : "../data/lena.jpg";
	const char* filename = "assets/a.jpg";
	Mat I = imread(filename, IMREAD_GRAYSCALE);
	if (I.empty()) {
		cout << "Error opening image" << endl;
		return -1;
	}
	/*
	 * DFT的性能取决于图像大小。对于图像尺寸来说，它往往是最快的，它是数字2,3和5的倍数。
	 * 因此，为了获得最大性能，通常最好将边界值填充到图像以获得具有这种特征的大小。
	 */
	//expand input image to optimal size
	Mat padded;
	int m = getOptimalDFTSize(I.rows); // 返回该最佳尺寸
	int n = getOptimalDFTSize(I.cols); // on the border add zero values
	// 扩展边界。以展开的图像（在所附像素与零初始化）的边界：
	copyMakeBorder(I, padded, 0, m - I.rows, 0, n - I.cols, BORDER_CONSTANT,
			Scalar::all(0));
	/*
	 * 傅里叶变换的结果很复杂。这意味着对于每个图像值，结果是两个图像值（每个组件一个）。
	 * 此外，频域范围远大于其空间对应范围。因此，我们通常至少以浮动格式存储它们。
	 * 因此，我们将输入图像转换为此类型，并使用另一个通道扩展它以保存复杂值：
	 */
	Mat planes[] = { Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F) };
	Mat complexI;
	merge(planes, 2, complexI);  // Add to the expanded another plane with zeros
	dft(complexI, complexI); // this way the result may fit in the source matrix
	// compute the magnitude and switch to logarithmic scale
	// => log(1 + sqrt(Re(DFT(I))^2 + Im(DFT(I))^2))
	split(complexI, planes);    // planes[0] = Re(DFT(I), planes[1] = Im(DFT(I))
	magnitude(planes[0], planes[1], planes[0]);         // planes[0] = magnitude
	Mat magI = planes[0];
	magI += Scalar::all(1);                    // switch to logarithmic scale
	log(magI, magI);
	// 裁剪光谱，如果它有奇数个行或列,因为上边加了
	// crop the spectrum, if it has an odd number of rows or columns
	magI = magI(Rect(0, 0, magI.cols & -2, magI.rows & -2));
	// rearrange the quadrants of Fourier image  so that the origin is at the image center
	int cx = magI.cols / 2;
	int cy = magI.rows / 2;
	Mat q0(magI, Rect(0, 0, cx, cy));   // Top-Left - Create a ROI per quadrant
	Mat q1(magI, Rect(cx, 0, cx, cy));  // Top-Right
	Mat q2(magI, Rect(0, cy, cx, cy));  // Bottom-Left
	Mat q3(magI, Rect(cx, cy, cx, cy)); // Bottom-Right
	Mat tmp;                      // swap quadrants (Top-Left with Bottom-Right)
	q0.copyTo(tmp);
	q3.copyTo(q0);
	tmp.copyTo(q3);
	q1.copyTo(tmp);                // swap quadrant (Top-Right with Bottom-Left)
	q2.copyTo(q1);
	tmp.copyTo(q2);
	normalize(magI, magI, 0, 1, NORM_MINMAX); // Transform the matrix with float values into a
											  // viewable image form (float between values 0 and 1).
	imshow("Input Image", I);    // Show the result
	imshow("spectrum magnitude", magI);
	waitKey();
	// 应用的想法是确定图像中存在的几何方向。例如，让我们看看文本是否是水平的？看一些文字，你会注意到文本行的形式也是水平线，字母形成一些垂直线。在傅立叶变换的情况下，也可以看到文本片段的这两个主要组成部分。让我们使用这个水平和旋转的图像关于文本。
	return 0;
}

class MyData {
public:
	MyData() :
			A(0), X(0), id() {
	}
	explicit MyData(int) :
			A(97), X(CV_PI), id("mydata1234") // explicit to avoid implicit conversion
	{
	}
	void write(FileStorage& fs) const       //Write serialization for this class
			{
		fs << "{" << "A" << A << "X" << X << "id" << id << "}";
	}
	void read(const FileNode& node)          //Read serialization for this class
			{
		A = (int) node["A"];
		X = (double) node["X"];
		id = (string) node["id"];
	}
public:
	// Data Members
	int A;
	double X;
	string id;
};
//These write and read functions must be defined for the serialization in FileStorage to work
 void write(FileStorage& fs, const std::string&, const MyData& x) {
	x.write(fs);
}
 void read(const FileNode& node, MyData& x, const MyData& default_value = // @suppress("Unused static function")
		MyData()) {
	if (node.empty())
		x = default_value;
	else
		x.read(node);
}
// This function will print our custom class to the console
static ostream& operator<<(ostream& out, const MyData& m) {
	out << "{ id = " << m.id << ", ";
	out << "X = " << m.X << ", ";
	out << "A = " << m.A << "}";
	return out;
}
/*
 * https://docs.opencv.org/4.0.1/dd/d74/tutorial_file_input_output_with_xml_yml.html
 */
int fileYamlXml() {
	string filename = "outputfile.xml";
	{ //write
		Mat R = Mat_<uchar>(3, 3);
		Mat T = Mat_<double>(3, 1);
		MyData m(1);
		FileStorage fs(filename, FileStorage::WRITE);
		fs << "iterationNr" << 100;
		fs << "strings" << "[";                        // text - string sequence
		fs << "image1.jpg" << "Awesomeness" << "../data/baboon.jpg";
		fs << "]";                                           // close sequence
		fs << "Mapping";                              // text - mapping
		fs << "{" << "One" << 1;
		fs << "Two" << 2 << "}";
		fs << "R" << R;                                      // cv::Mat
		fs << "T" << T;
		fs << "MyData" << m;                         // your own data structures
		fs.release();                                       // explicit close
		cout << "Write Done." << endl;
	}
	{                                       //read
		cout << endl << "Reading: " << endl;
		FileStorage fs;
		/*在将任何内容写入此类文件之前，您需要打开它并在最后将其关闭。
		 * OpenCV中的XML / YAML数据结构是cv :: FileStorage。
		 * 要指定此文件绑定到您的硬盘驱动器上的结构，您可以使用其构造函数或open（）函数：
		 * 您使用第二个参数中的任何一个都是一个常量，
		 * 指定您可以对它们执行的操作类型：WRITE，READ或APPEND。
		 * 文件名中指定的扩展名还确定将使用的输出格式。
		 * 如果指定* .xml.gz *等扩展名，则输出甚至可以压缩。
		 */
		fs.open(filename, FileStorage::READ);
		int itNr;
		//fs["iterationNr"] >> itNr;
		itNr = (int) fs["iterationNr"];
		cout << itNr;
		if (!fs.isOpened()) {
			cerr << "Failed to open " << filename << endl;
			return 1;
		}
		FileNode n = fs["strings"];           // Read string sequence - Get node
		if (n.type() != FileNode::SEQ) {
			cerr << "strings is not a sequence! FAIL" << endl;
			return 1;
		}
		FileNodeIterator it = n.begin(), it_end = n.end(); // Go through the node
		for (; it != it_end; ++it)
			cout << (string) *it << endl;
		n = fs["Mapping"];                      // Read mappings from a sequence
		cout << "Two  " << (int) (n["Two"]) << "; ";
		cout << "One  " << (int) (n["One"]) << endl << endl;
		MyData m;
		Mat R, T;
		fs["R"] >> R;                                      // Read cv::Mat
		fs["T"] >> T;
		fs["MyData"] >> m;                           // Read your own structure_
		cout << endl << "R = " << R << endl;
		cout << "T = " << T << endl << endl;
		cout << "MyData = " << endl << m << endl << endl;
		//Show default behavior for non existing nodes
		cout
				<< "Attempt to read NonExisting (should initialize the data structure with its default).";
		fs["NonExisting"] >> m;
		cout << endl << "NonExisting = " << endl << m << endl;
	}
	cout << endl << "Tip: Open up " << filename
			<< " with a text editor to see the serialized data." << endl;
	return 0;
}

/*
 * 多线程
 * https://docs.opencv.org/4.0.1/d7/dff/tutorial_how_to_use_OpenCV_parallel_for_.html
 */
Lesson2OperationsImages::~Lesson2OperationsImages() {
}

