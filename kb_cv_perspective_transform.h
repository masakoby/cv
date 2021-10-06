#include <vector>
#include <opencv2/opencv.hpp>

#pragma once

namespace kb
{
	//	���e�ϊ��s��̋t�s����v�Z����
	int inversePerspectiveTransform(
		cv::Mat& matP, //	���e�ϊ��s��
		cv::Size& sz1, //	�摜�T�C�Y
		cv::Mat& matP_inv,
		cv::Point2f pt_range[2]
	);

	int updateRangePerspectiveTransform(
		std::vector<cv::Mat>& v_P,
		cv::Size& sz0,
		double rangex_out[2],
		double rangey_out[2]
	);

	//	���e�ϊ��s��ɂ���āA�摜�[���W�̃}�b�s���O��̍ő�ŏ����X�V����
	int updateRangePerspectiveTransform(
		cv::Mat& matP, cv::Size& sz0,
		double rangex[2], double rangey[2]);

	int calcPerspectiveTransform(
		cv::Point2f& pt,
		std::vector<cv::Mat>& v_P1,
		std::vector<cv::Point2f>& v_pt_out
	);

	int forward_P(
		cv::Mat& matP_bf,
		cv::Mat& matP_in,
		cv::Mat& matP_out,
		cv::Size& sz0
	);

};
