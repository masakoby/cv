

#include <opencv2/opencv.hpp>

#pragma once

namespace kb
{
	int saveAsSTL_64F(
		const std::string& path1,
		cv::Mat& mat64F
	);
};
