#include <vector>

#include <opencv2/opencv.hpp>

#pragma once

namespace kb
{
	//	
	void drawContours(
		cv::Mat& mat1,
		std::vector<std::vector<std::vector<cv::Point>>>& vv_contours,
		cv::Mat& matV,
		int thickness,
		double ratio_reduce	//	縮小倍率(0.1以下にすると、縮小機能オフ）
	);

};
