#include <opencv2/opencv.hpp>

#pragma once

namespace kb
{
	//	指定面積以下は除去
	int remove_regions_8n(
		cv::Mat& mat1,
		cv::Mat& mat_out,
		int	squareRemove
	);

};
