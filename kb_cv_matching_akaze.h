#include <vector>

#include <opencv2/opencv.hpp>

#pragma once

namespace kb
{
	int match_akaze(
		cv::Mat& mat1,
		cv::Mat& mat2,
		std::vector<cv::DMatch>& v_dm,
		std::vector<cv::KeyPoint>& v_kp1,
		std::vector<cv::KeyPoint>& v_kp2,

		double thr = 0.001,
		int mode_matching=0					//	0 AND(双方向のみ）
											//	1 OR(すべてのパターン)
	);
};
