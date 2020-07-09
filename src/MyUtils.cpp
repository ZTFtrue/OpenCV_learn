/*
 * MyUtils.cpp
 *
 *  Created on: Mar 29, 2019
 *      Author: ztftrue
 */

#include "MyUtils.h"

MyUtils::MyUtils() {

}
void MyUtils::drawBoundingBox(Mat image, vector<Point2f> bb) {
	for (unsigned i = 0; i < bb.size() - 1; i++) {
		line(image, bb[i], bb[i + 1], Scalar(0, 0, 255), 2);
	}
	line(image, bb[bb.size() - 1], bb[0], Scalar(0, 0, 255), 2);
}

void MyUtils::drawStatistics(Mat image, const Stats& stats) {
	static const int font = FONT_HERSHEY_PLAIN;
	stringstream str1, str2, str3, str4;

	str1 << "Matches: " << stats.matches;
	str2 << "Inliers: " << stats.inliers;
	str3 << "Inlier ratio: " << setprecision(2) << stats.ratio;
	str4 << "FPS: " << std::fixed << setprecision(2) << stats.fps;

	putText(image, str1.str(), Point(0, image.rows - 120), font, 2,
			Scalar::all(255), 3);
	putText(image, str2.str(), Point(0, image.rows - 90), font, 2,
			Scalar::all(255), 3);
	putText(image, str3.str(), Point(0, image.rows - 60), font, 2,
			Scalar::all(255), 3);
	putText(image, str4.str(), Point(0, image.rows - 30), font, 2,
			Scalar::all(255), 3);
}

void MyUtils::printStatistics(string name, Stats stats) {
	cout << name << endl;
	cout << "----------" << endl;

	cout << "Matches " << stats.matches << endl;
	cout << "Inliers " << stats.inliers << endl;
	cout << "Inlier ratio " << setprecision(2) << stats.ratio << endl;
	cout << "Keypoints " << stats.keypoints << endl;
	cout << "FPS " << std::fixed << setprecision(2) << stats.fps << endl;
	cout << endl;
}

vector<Point2f> MyUtils::Points(vector<KeyPoint> keypoints) {
	vector<Point2f> res;
	for (unsigned i = 0; i < keypoints.size(); i++) {
		res.push_back(keypoints[i].pt);
	}
	return res;
}
MyUtils::~MyUtils() {
}

