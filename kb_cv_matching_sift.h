#include <vector>

#include <opencv2/opencv.hpp>

#pragma once

namespace kb
{
	int match_sift(
		cv::Mat& mat1,
		cv::Mat& mat2,
		std::vector<cv::DMatch>& v_dm,
		std::vector<cv::KeyPoint>& v_kp1,
		std::vector<cv::KeyPoint>& v_kp2,

		double contrast_thr = 0.04,
		double edge_thr = 10.0,
		double sigma = 1.6
	);

};
