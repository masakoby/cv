#include <opencv2/opencv.hpp>

#pragma once

namespace kb
{
	int fill_hole(
		cv::Mat& mat1,
		cv::Mat& mat_out,
		int	square_hole
	);

};
