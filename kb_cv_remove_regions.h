#include <opencv2/opencv.hpp>

#pragma once

namespace kb
{
	//	�w��ʐψȉ��͏���
	int remove_regions_8n(
		cv::Mat& mat1,
		cv::Mat& mat_out,
		int	squareRemove
	);

};
