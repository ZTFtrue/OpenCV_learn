/*
 * LessonAFeaturesFramework.cpp
 *
 *  Created on: Mar 28, 2019
 *      Author: ztftrue
 */

#include <LessonAFeaturesFramework.h>
#undef	MAX
#define MAX(a, b)  (((a) > (b)) ? (a) : (b))

//https://docs.opencv.org/4.0.1/d9/d97/tutorial_table_of_content_features2d.html
LessonAFeaturesFramework::LessonAFeaturesFramework() {
}

int thresh = 200;
int max_thresh = 255;
const char* source_window = "Source image";
const char* corners_window = "Corners detected";
static Mat src_gray;
static Mat src;
void cornerHarris_demo(int, void*) {
	int blockSize = 2;
	int apertureSize = 3;
	double k = 0.04;
	Mat dst = Mat(src.size(), CV_32FC1);
	cornerHarris(src_gray, dst, blockSize, apertureSize, k);
	Mat dst_norm, dst_norm_scaled;
	normalize(dst, dst_norm, 0, 255, NORM_MINMAX, CV_32FC1, Mat());
	convertScaleAbs(dst_norm, dst_norm_scaled);
	for (int i = 0; i < dst_norm.rows; i++) {
		for (int j = 0; j < dst_norm.cols; j++) {
			if ((int) dst_norm.at<float>(i, j) > thresh) {
				circle(dst_norm_scaled, Point(j, i), 5, Scalar(0), 2, 8, 0);
			}
		}
	}
	namedWindow(corners_window);
	imshow(corners_window, dst_norm_scaled);
}
/**
 * https://docs.opencv.org/4.0.1/d4/d7d/tutorial_harris_detector.html
 */
int LessonAFeaturesFramework::harrisCornerDetector() {
	src = imread("a.jpg");
	if (src.empty()) {
		cout << "Could not open or find the image!\n" << endl;
		return -1;
	}
	cvtColor(src, src_gray, COLOR_BGR2GRAY);
	namedWindow(source_window);
	createTrackbar("Threshold: ", source_window, &thresh, max_thresh,
			cornerHarris_demo);
	imshow(source_window, src);
	cornerHarris_demo(0, 0);
	waitKey();
	return 0;
}

int maxCorners = 23;
int maxTrackbar = 100;
RNG rng(12345);
void goodFeaturesToTrack_Demo(int, void*) {
	maxCorners = MAX(maxCorners, 1);
	vector<Point2f> corners;
	double qualityLevel = 0.01;
	double minDistance = 10;
	int blockSize = 3, gradientSize = 3;
	bool useHarrisDetector = false;
	double k = 0.04;
	Mat copy = src.clone();
	goodFeaturesToTrack(src_gray, corners, maxCorners, qualityLevel,
			minDistance, Mat(), blockSize, gradientSize, useHarrisDetector, k);
	cout << "** Number of corners detected: " << corners.size() << endl;
	int radius = 4;
	for (size_t i = 0; i < corners.size(); i++) {
		circle(copy, corners[i], radius,
				Scalar(rng.uniform(0, 255), rng.uniform(0, 256),
						rng.uniform(0, 256)), FILLED);
	}
	namedWindow(source_window);
	imshow(source_window, copy);
}
int LessonAFeaturesFramework::shiTomasiCornerDetector() {
	src = imread("a.jpg");
	if (src.empty()) {
		cout << "Could not open or find the image!\n" << endl;
		return -1;
	}
	cvtColor(src, src_gray, COLOR_BGR2GRAY);
	namedWindow(source_window);
	createTrackbar("Max corners:", source_window, &maxCorners, maxTrackbar,
			goodFeaturesToTrack_Demo);
	imshow(source_window, src);
	goodFeaturesToTrack_Demo(0, 0);
	waitKey();
	return 0;
}

Mat myHarris_dst, myHarris_copy, Mc;
Mat myShiTomasi_dst, myShiTomasi_copy;
int myShiTomasi_qualityLevel = 50;
int myHarris_qualityLevel = 50;
int max_qualityLevel = 100;
double myHarris_minVal, myHarris_maxVal;
double myShiTomasi_minVal, myShiTomasi_maxVal;
const char* myHarris_window = "My Harris corner detector";
const char* myShiTomasi_window = "My Shi Tomasi corner detector";

void myShiTomasi_function(int, void*) {
	myShiTomasi_copy = src.clone();
	myShiTomasi_qualityLevel = MAX(myShiTomasi_qualityLevel, 1);
	for (int i = 0; i < src_gray.rows; i++) {
		for (int j = 0; j < src_gray.cols; j++) {
			if (myShiTomasi_dst.at<float>(i, j)
					> myShiTomasi_minVal
							+ (myShiTomasi_maxVal - myShiTomasi_minVal)
									* myShiTomasi_qualityLevel
									/ max_qualityLevel) {
				circle(myShiTomasi_copy, Point(j, i), 4,
						Scalar(rng.uniform(0, 256), rng.uniform(0, 256),
								rng.uniform(0, 256)), FILLED);
			}
		}
	}
	imshow(myShiTomasi_window, myShiTomasi_copy);
}
void myHarris_function(int, void*) {
	myHarris_copy = src.clone();
	myHarris_qualityLevel = MAX(myHarris_qualityLevel, 1);
	for (int i = 0; i < src_gray.rows; i++) {
		for (int j = 0; j < src_gray.cols; j++) {
			if (Mc.at<float>(i, j)
					> myHarris_minVal
							+ (myHarris_maxVal - myHarris_minVal)
									* myHarris_qualityLevel
									/ max_qualityLevel) {
				circle(myHarris_copy, Point(j, i), 4,
						Scalar(rng.uniform(0, 256), rng.uniform(0, 256),
								rng.uniform(0, 256)), FILLED);
			}
		}
	}
	imshow(myHarris_window, myHarris_copy);
}

int LessonAFeaturesFramework::yourOwnCornerDetector() {
	src = imread("a.jpg");
	if (src.empty()) {
		cout << "Could not open or find the image!\n" << endl;
		return -1;
	}
	cvtColor(src, src_gray, COLOR_BGR2GRAY);
	int blockSize = 3, apertureSize = 3;
	cornerEigenValsAndVecs(src_gray, myHarris_dst, blockSize, apertureSize);
	/* calculate Mc */
	Mc = Mat(src_gray.size(), CV_32FC1);
	for (int i = 0; i < src_gray.rows; i++) {
		for (int j = 0; j < src_gray.cols; j++) {
			float lambda_1 = myHarris_dst.at<Vec6f>(i, j)[0];
			float lambda_2 = myHarris_dst.at<Vec6f>(i, j)[1];
			Mc.at<float>(i, j) = lambda_1 * lambda_2
					- 0.04f * pow((lambda_1 + lambda_2), 2);
		}
	}
	minMaxLoc(Mc, &myHarris_minVal, &myHarris_maxVal);
	/* Create Window and Trackbar */
	namedWindow(myHarris_window);
	createTrackbar("Quality Level:", myHarris_window, &myHarris_qualityLevel,
			max_qualityLevel, myHarris_function);
	myHarris_function(0, 0);
	cornerMinEigenVal(src_gray, myShiTomasi_dst, blockSize, apertureSize);
	minMaxLoc(myShiTomasi_dst, &myShiTomasi_minVal, &myShiTomasi_maxVal);
	/* Create Window and Trackbar */
	namedWindow(myShiTomasi_window);
	createTrackbar("Quality Level:", myShiTomasi_window,
			&myShiTomasi_qualityLevel, max_qualityLevel, myShiTomasi_function);
	myShiTomasi_function(0, 0);
	waitKey();
	return 0;
}

int LessonAFeaturesFramework::detectingCornersLocationsInSubpixels() {

	return 0;
}
/* 由于SURF
 * https://docs.opencv.org/4.0.1/d7/d66/tutorial_feature_detection.html
 * https://docs.opencv.org/4.0.1/d5/dde/tutorial_feature_description.html
 */
int LessonAFeaturesFramework::features2dDetection() {
	Mat src = imread("a.jpg");
	if (src.empty()) {
		cout << "Could not open or find the image!\n" << endl;
		return -1;
	}
	//-- Step 1: Detect the keypoints using SURF Detector
	int minHessian = 400;
//	Ptr<SURF> detector = SURF::create(minHessian);
//	std::vector<KeyPoint> keypoints;
//	detector->detect(src, keypoints);
	//-- Draw keypoints
	Mat img_keypoints;
//	drawKeypoints(src, keypoints, img_keypoints);
	//-- Show detected (drawn) keypoints
	imshow("SURF Keypoints", img_keypoints);
	waitKey();
	return 0;
}
int LessonAFeaturesFramework::featureMatchingFLANN() {
	Mat img1 = imread("a.jpg");
	Mat img2 = imread("a.jpg");
	if (img1.empty() || img2.empty()) {
		cout << "Could not open or find the image!\n" << endl;
		return -1;
	}
	//-- Step 1: Detect the keypoints using SURF Detector, compute the descriptors
	int minHessian = 400;
//	Ptr<SURF> detector = SURF::create(minHessian);
	std::vector<KeyPoint> keypoints1, keypoints2;
	Mat descriptors1, descriptors2;
//	detector->detectAndCompute(img1, noArray(), keypoints1, descriptors1);
//	detector->detectAndCompute(img2, noArray(), keypoints2, descriptors2);
	//-- Step 2: Matching descriptor vectors with a FLANN based matcher
	// Since SURF is a floating-point descriptor NORM_L2 is used
	Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create(
			DescriptorMatcher::FLANNBASED);
	std::vector<std::vector<DMatch> > knn_matches;
	matcher->knnMatch(descriptors1, descriptors2, knn_matches, 2);
	//-- Filter matches using the Lowe's ratio test
	const float ratio_thresh = 0.7f;
	std::vector<DMatch> good_matches;
	for (size_t i = 0; i < knn_matches.size(); i++) {
		if (knn_matches[i][0].distance
				< ratio_thresh * knn_matches[i][1].distance) {
			good_matches.push_back(knn_matches[i][0]);
		}
	}
	//-- Draw matches
	Mat img_matches;
	drawMatches(img1, keypoints1, img2, keypoints2, good_matches, img_matches,
			Scalar::all(-1), Scalar::all(-1), std::vector<char>(),
			DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
	//-- Show detected matches
	imshow("Good Matches", img_matches);
	waitKey();
	return 0;

	return 0;
}
int LessonAFeaturesFramework::feature2DHomographyFindObject() {
	return 0;
}
LessonAFeaturesFramework::~LessonAFeaturesFramework() {
//	source_window=NU;
//		corners_window="Corners detected";
//		thresh = 200;
//		max_thresh = 255;
}

