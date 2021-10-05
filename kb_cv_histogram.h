#include <opencv2/opencv.hpp>

#pragma once

namespace kb {
	int histogram256_32F(cv::Mat& mat32F, cv::Mat& hist32F, float step);
	int histogram256_32F(cv::Mat& mat32F, std::vector<float>& hist, float step);

	int histogram256_32F(cv::Mat& mat32F, cv::Mat& hist32F);
	int histogram256_32F(cv::Mat& mat32F, std::vector<float>& hist);

};
