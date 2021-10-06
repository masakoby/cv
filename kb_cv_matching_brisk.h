#include <vector>

#include <opencv2/opencv.hpp>

#pragma once

namespace kb
{
	int match_BRISK(
		cv::Mat& mat1,
		cv::Mat& mat2,
		std::vector<cv::DMatch>& v_dm,
		std::vector<cv::KeyPoint>& v_kp1,
		std::vector<cv::KeyPoint>& v_kp2,
		int thres1,// = 30,
		int octaves,// = 3,
		float patternScale// = 1.0f,
	);

};
