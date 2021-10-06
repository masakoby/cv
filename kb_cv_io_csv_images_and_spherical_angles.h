#include <vector>
#include <opencv2/opencv.hpp>

#pragma once

namespace kb
{
	int load_csv(
		std::string& path,
		std::vector< std::string >& filenames,
		std::vector<cv::Point3f>& v_angle,
		std::vector<int>& v_flag
	);
};
