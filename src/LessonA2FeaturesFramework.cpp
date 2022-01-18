/*
 * LessonA2FeaturesFramework.cpp
 *
 *  Created on: Mar 29, 2019
 *      Author: ztftrue
 */

#include "LessonA2FeaturesFramework.h"

using namespace my_cv;

LessonA2FeaturesFramework::LessonA2FeaturesFramework() {

}
const double akaze_thresh = 3e-4; // AKAZE detection threshold set to locate about 1000 keypoints
const int stats_update_period = 10; // On-screen statistics are updated every 10 frames

int LessonA2FeaturesFramework::AKAZEandORBplanar() {
	string input_path = "assets/video.mp4";
	string video_name = input_path;
	VideoCapture video_in;
	if ((isdigit(input_path[0]) && input_path.size() == 1)) {
		int camera_no = input_path[0] - '0';
		video_in.open(camera_no);
	} else {
		video_in.open(video_name);
	}
	if (!video_in.isOpened()) {
		cerr << "Couldn't open " << video_name << endl;
		return 1;
	}
	Stats stats, akaze_stats, orb_stats;
	Ptr<AKAZE> akaze = AKAZE::create();
	akaze->setThreshold(akaze_thresh);
	Ptr<ORB> orb = ORB::create();
	Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create(
			"BruteForce-Hamming");
	my_cv::Tracker akaze_tracker(akaze, matcher);
	my_cv::Tracker orb_tracker(orb, matcher);
	Mat frame;
	namedWindow(video_name, WINDOW_NORMAL);
	cout << "\nPress any key to stop the video and select a bounding box"
			<< endl;
	while (waitKey(1) < 1) {
		video_in >> frame;
		cv::resizeWindow(video_name, frame.size());
		imshow(video_name, frame);
	}
	vector<Point2f> bb;
	cv::Rect uBox = cv::selectROI(video_name, frame);
	bb.push_back(
			cv::Point2f(static_cast<float>(uBox.x),
					static_cast<float>(uBox.y)));
	bb.push_back(
			cv::Point2f(static_cast<float>(uBox.x + uBox.width),
					static_cast<float>(uBox.y)));
	bb.push_back(
			cv::Point2f(static_cast<float>(uBox.x + uBox.width),
					static_cast<float>(uBox.y + uBox.height)));
	bb.push_back(
			cv::Point2f(static_cast<float>(uBox.x),
					static_cast<float>(uBox.y + uBox.height)));
	akaze_tracker.setFirstFrame(frame, bb, "AKAZE", stats);
	orb_tracker.setFirstFrame(frame, bb, "ORB", stats);
	Stats akaze_draw_stats, orb_draw_stats;
	Mat akaze_res, orb_res, res_frame;
	int i = 0;
	for (;;) {
		i++;
		bool update_stats = (i % stats_update_period == 0);
		video_in >> frame;
		// stop the program if no more images
		if (frame.empty())
			break;
		akaze_res = akaze_tracker.process(frame, stats);
		akaze_stats += stats;
		if (update_stats) {
			akaze_draw_stats = stats;
		}
		orb->setMaxFeatures(stats.keypoints);
		orb_res = orb_tracker.process(frame, stats);
		orb_stats += stats;
		if (update_stats) {
			orb_draw_stats = stats;
		}
		myUtils.drawStatistics(akaze_res, akaze_draw_stats);
		myUtils.drawStatistics(orb_res, orb_draw_stats);
		vconcat(akaze_res, orb_res, res_frame);
		cv::imshow(video_name, res_frame);
		if (waitKey(1) == 27)
			break; //quit on ESC button
	}
	akaze_stats /= i - 1;
	orb_stats /= i - 1;
	myUtils.printStatistics("AKAZE", akaze_stats);
	myUtils.printStatistics("ORB", orb_stats);
	return 0;
}

int LessonA2FeaturesFramework::AKAZEmatching() {
	// 换成tree是最好测试的
	    Mat img1 = imread("assets/a.jpg", IMREAD_GRAYSCALE);
	    Mat img2 = imread("assets/a.jpg", IMREAD_GRAYSCALE);

	    Mat homography;
	    FileStorage fs("assets/tree", FileStorage::READ);
	    fs.getFirstTopLevelNode() >> homography;
	    //! [load]

	    //! [AKAZE]
	    vector<KeyPoint> kpts1, kpts2;
	    Mat desc1, desc2;

	    Ptr<AKAZE> akaze = AKAZE::create();
	    akaze->detectAndCompute(img1, noArray(), kpts1, desc1);
	    akaze->detectAndCompute(img2, noArray(), kpts2, desc2);
	    //! [AKAZE]

	    //! [2-nn matching]
	    BFMatcher matcher(NORM_HAMMING);
	    vector< vector<DMatch> > nn_matches;
	    matcher.knnMatch(desc1, desc2, nn_matches, 2);
	    //! [2-nn matching]

	    //! [ratio test filtering]
	    vector<KeyPoint> matched1, matched2;
	    for(size_t i = 0; i < nn_matches.size(); i++) {
	        DMatch first = nn_matches[i][0];
	        float dist1 = nn_matches[i][0].distance;
	        float dist2 = nn_matches[i][1].distance;

	        if(dist1 < nn_match_ratio * dist2) {
	            matched1.push_back(kpts1[first.queryIdx]);
	            matched2.push_back(kpts2[first.trainIdx]);
	        }
	    }
	    //! [ratio test filtering]

	    //! [homography check]
	    vector<DMatch> good_matches;
	    vector<KeyPoint> inliers1, inliers2;
	    for(size_t i = 0; i < matched1.size(); i++) {
	    	// TODO Documents
	        Mat col = Mat::ones(3, 1, CV_8UC3).a;
	        col.at<double>(0) = matched1[i].pt.x;
	        col.at<double>(1) = matched1[i].pt.y;

	        col = homography * col;
	        col /= col.at<double>(2);
	        double dist = sqrt( pow(col.at<double>(0) - matched2[i].pt.x, 2) +
	                            pow(col.at<double>(1) - matched2[i].pt.y, 2));

	        if(dist < inlier_threshold) {
	            int new_i = static_cast<int>(inliers1.size());
	            inliers1.push_back(matched1[i]);
	            inliers2.push_back(matched2[i]);
	            good_matches.push_back(DMatch(new_i, new_i, 0));
	        }
	    }
	    //! [homography check]

	    //! [draw final matches]
	    Mat res;
	    drawMatches(img1, inliers1, img2, inliers2, good_matches, res);
	    imwrite("akaze_result.png", res);

	    double inlier_ratio = inliers1.size() / (double) matched1.size();
	    cout << "A-KAZE Matching Results" << endl;
	    cout << "*******************************" << endl;
	    cout << "# Keypoints 1:                        \t" << kpts1.size() << endl;
	    cout << "# Keypoints 2:                        \t" << kpts2.size() << endl;
	    cout << "# Matches:                            \t" << matched1.size() << endl;
	    cout << "# Inliers:                            \t" << inliers1.size() << endl;
	    cout << "# Inliers Ratio:                      \t" << inlier_ratio << endl;
	    cout << endl;

	    imshow("result", res);
	    waitKey();
	    //! [draw final matches]

	    return 0;
}

LessonA2FeaturesFramework::~LessonA2FeaturesFramework() {
}

