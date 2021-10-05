#include <vector>

#include <opencv2/opencv.hpp>

#pragma once

namespace kb
{
	//	
	void drawMargin(
		cv::Mat& mat8UC3,
		cv::Vec3b a,
		int thickness
	);

};
