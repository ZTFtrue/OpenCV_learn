/*
 * MyTracker.h
 *
 *  Created on: Mar 29, 2019
 *      Author: ztftrue
 */

#ifndef SRC_TRACKER_H_
#define SRC_TRACKER_H_
#include <iostream>
#include <opencv4/opencv2/opencv.hpp>
#include <opencv4/opencv2/core.hpp>
#include <opencv4/opencv2/imgcodecs.hpp>
#include <opencv4/opencv2/imgproc.hpp>
#include <opencv4/opencv2/features2d.hpp>
#include <opencv4/opencv2/core/cvdef.h>
#include <opencv4/opencv2/calib3d.hpp>
#include <opencv4/opencv2/videoio.hpp>
#include <iostream>
#include <iomanip>
#include "MyUtils.h" // Drawing and printing functions
#include "stats.h" // Stats structure definition

using namespace cv;
using namespace std;

const double ransac_thresh = 2.5f; // RANSAC inlier threshold
const int bb_min_inliers = 100; // Minimal number of inliers to draw bounding box
const double nn_match_ratio = 0.8f; // Nearest-neighbour matching ratio

class Tracker {

public:
	Tracker(Ptr<Feature2D> _detector, Ptr<DescriptorMatcher> _matcher) :
			detector(_detector), matcher(_matcher) {
	}
	void setFirstFrame(const cv::Mat frame, vector<Point2f> bb, string title,
			Stats& stats);
	Mat process(const Mat frame, Stats& stats);
	Ptr<Feature2D> getDetector() {
		return detector;
	}
	Tracker();
	virtual ~Tracker();
protected:
    MyUtils myUtils;
	Ptr<Feature2D> detector;
	Ptr<DescriptorMatcher> matcher;
	Mat first_frame, first_desc;
	vector<KeyPoint> first_kp;
	vector<Point2f> object_bb;

};

#endif /* SRC_TRACKER_H_ */
