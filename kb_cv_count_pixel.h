#include <opencv2/opencv.hpp>

#pragma once

namespace kb
{
	//	�l���P�ȏ�̃s�N�Z�����J�E���g����
	int count_pixel_non_zero(cv::Mat& mat8U);
	int count_pixel_non_zero(cv::Mat& mat8U, int x0, int y0, int width, int height);
	int count_pixel_non_zero(cv::Mat& mat8U, int x0, int y0, int width, int height, std::vector<int>& hist);

	//	�ʓx��臒l�ȏ゠��s�N�Z�����J�E���g����
	int count_pixel_Saturation(cv::Mat& matRGB, int threshold_Sat);

	//	�G�b�W�̃s�N�Z�������J�E���g����
	int count_pixel_Edge(cv::Mat& mat8U, int threshold_Edge);

};
