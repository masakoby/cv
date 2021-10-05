#include <vector>

#include <opencv2/opencv.hpp>

#pragma once

namespace kb
{
	//	�Ή��_�̉���
	//		opencv�̑Ή��_�����֐��́A
	//		cv::KeyPoint�I�u�W�F�N�g�Ŏ󂯓n���B
	//		�Q�������W�z���n���ĕ`�悷��悤�Ɋ֐����쐬����
	//		�����̍ہA�摜�𑜓x�𗎂Ƃ��@�\���t��
	void drawMatches(
		cv::Mat& mat1,
		cv::Mat& mat2,
		std::vector<cv::Point2f>& mp1,
		std::vector<cv::Point2f>& mp2,
		cv::Mat& matV12,
		double ratio_reduce	//	�k���{��(0.1�ȉ��ɂ���ƁA�k���@�\�I�t�j
		);

};
