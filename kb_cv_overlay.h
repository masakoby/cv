#include <opencv2/opencv.hpp>

#pragma once

namespace kb
{
	//	マスク領域を指定の色に塗る
	void overlay(cv::Mat& matVis, cv::Mat& mask, cv::Scalar color, double ratio = -1);
	//	黒以外のRGBマスク画像の色をオーバーレイする。
	void overlayRGB(cv::Mat& matVis, cv::Mat& maskRGB, double ratio = -1);

};
