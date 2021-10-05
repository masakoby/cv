#include <vector>

#include <opencv2/opencv.hpp>

#pragma once

namespace kb
{
	//	画像に点を描画する。特徴点などの描画に用いる
	void drawPoints(
		cv::Mat& mat1,
		cv::Mat& mat1_out,
		std::vector<cv::Point2f>& vp, 
		double ratio,
		int radius = 5,
		cv::Scalar color=cv::Scalar(0,255,0));
};
