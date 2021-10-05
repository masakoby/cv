#include <opencv2/opencv.hpp>

#pragma once

namespace kb
{
	//	�̈悪�͂ݏo�Ă��R�s�[����
	int copyTo_8UC3(cv::Mat& mat1, cv::Rect& rect, cv::Mat& mat2, cv::Vec3b bk);

	//	�}�X�N�̈�̂݃R�s�[����
	//	�̈悪�͂ݏo�Ă��R�s�[����
	int copyTo_8UC3(cv::Mat& mat1, cv::Rect& rect, cv::Mat& mask, cv::Mat& mat2, cv::Vec3b bk);


	//
	//	�S�̉摜����ROI��؂�o���B�̈悪�͂ݏo�Ă��R�s�[����
	//	
	int copyTo_8UC1(cv::Mat& mat1, cv::Rect& rect1, cv::Mat& mat2);

	//
	//	������ROI�摜��S�̉摜�֒���t����Ƃ��ɗp����
	//	
	int copyTo_8UC1(cv::Mat& mat1, cv::Mat& mask1, cv::Mat& mat2, cv::Point& pt2);

};
