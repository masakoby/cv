#include <opencv2/opencv.hpp>

#pragma once

namespace kb {
	int RGB2Lum_32F(cv::Mat& matRGB, cv::Mat& mat32F);
};
