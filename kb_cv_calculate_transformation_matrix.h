#include <vector>

#include <opencv2/opencv.hpp>

#pragma once

namespace kb
{
	int calculate_affine_transformation_matrix(
		std::vector<cv::Point2f>& mp1,
		std::vector<cv::Point2f>& mp2,
		cv::Mat& matAf_3x3,
		double ratio_mag
		);
};
