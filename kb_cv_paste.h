#include <opencv2/opencv.hpp>

#pragma once

namespace kb
{
	//	�}�b�`���O�̌���
	//	�ϊ��s����w�肵�ăI�[�o�[���C
	//
	int pasteTo(
		cv::Mat& matBase,	//	
		cv::Mat& matOver,	//	
		cv::Mat& matP,		//	�ϊ��s��
		cv::Mat& matOut,	//	
		int mode			//	
	);
};
