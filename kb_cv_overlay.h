#include <opencv2/opencv.hpp>

#pragma once

namespace kb
{
	//	�}�X�N�̈���w��̐F�ɓh��
	void overlay(cv::Mat& matVis, cv::Mat& mask, cv::Scalar color, double ratio = -1);
	//	���ȊO��RGB�}�X�N�摜�̐F���I�[�o�[���C����B
	void overlayRGB(cv::Mat& matVis, cv::Mat& maskRGB, double ratio = -1);

};
