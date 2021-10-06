#include <opencv2/opencv.hpp>

#pragma once

namespace kb
{
	int matching_spherical_pos(
		std::vector<cv::Point3f>& vp1,
		std::vector<cv::Point3f>& vp2,
		double angle[3],
		double matR[9],
		double coef_lossfunc,
		double range_angle[3],
		bool mode_stdout,
		int num_threads,
		int max_num_iterations);
};
