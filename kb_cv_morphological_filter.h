#include <opencv2/opencv.hpp>
#include <vector>

#pragma once

namespace kb
{
	int opening(cv::Mat& mat1, cv::Mat& mat1_out, int num_opening);
	int closing(cv::Mat& mat1, cv::Mat& mat1_out, int num_closing);
};
