#include <vector>

#include <opencv2/opencv.hpp>

#pragma once

namespace kb
{
	int match_orb(
		cv::Mat& mat1,
		cv::Mat& mat2,
		std::vector<cv::DMatch>& v_dm,
		std::vector<cv::KeyPoint>& v_kp1,
		std::vector<cv::KeyPoint>& v_kp2,
		int nfeatures = 500,
		float scaleFactor = 1.2f,
		int nlevels = 8,
		int edgeThreshold = 31,
		int firstLevel = 0,
		int WTA_K = 2,
		int scoreType = cv::ORB::HARRIS_SCORE,
		int patchSize = 31,
		int fastThreshold = 20
	);

};
