#include <opencv2/opencv.hpp>

#pragma once

namespace kb
{
	//	値が１以上のピクセルをカウントする
	int count_pixel_non_zero(cv::Mat& mat8U);
	int count_pixel_non_zero(cv::Mat& mat8U, int x0, int y0, int width, int height);
	int count_pixel_non_zero(cv::Mat& mat8U, int x0, int y0, int width, int height, std::vector<int>& hist);

	//	彩度が閾値以上あるピクセルをカウントする
	int count_pixel_Saturation(cv::Mat& matRGB, int threshold_Sat);

	//	エッジのピクセル数をカウントする
	int count_pixel_Edge(cv::Mat& mat8U, int threshold_Edge);

};
