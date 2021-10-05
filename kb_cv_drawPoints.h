#include <vector>

#include <opencv2/opencv.hpp>

#pragma once

namespace kb
{
	//	�摜�ɓ_��`�悷��B�����_�Ȃǂ̕`��ɗp����
	void drawPoints(
		cv::Mat& mat1,
		cv::Mat& mat1_out,
		std::vector<cv::Point2f>& vp, 
		double ratio,
		int radius = 5,
		cv::Scalar color=cv::Scalar(0,255,0));
};
