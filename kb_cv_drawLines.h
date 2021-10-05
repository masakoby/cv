#include <vector>

#include <opencv2/opencv.hpp>

#pragma once

namespace kb
{
	void drawLines(
		cv::Mat& mat1,
		std::vector<cv::Point2f>& vp,
		cv::Scalar color,
		int thickness,
		int close);
};
