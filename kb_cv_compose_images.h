#include <vector>
#include <opencv2/opencv.hpp>

#pragma once

namespace kb
{

	//	���e�ϊ��s�񃊃X�g���g�����������Q�Ƃɂ��摜����
	//	�������Q�ƂȂ̂ŁA�����摜�ɂ����ĉ�f�������ĕ\�������\��������
	//	�������V���v���ŁA�l�q���̏����Ƃ��Ă͓K���Ă���
	int compose_images_forward(
		std::vector<cv::Mat>& v_images,
		std::vector<cv::Mat>& v_af,
		double rangex[2], double rangey[2],
		cv::Mat& matV
	);

	int compose_images_backward(
		std::vector<cv::Mat>& v_images,
		std::vector<cv::Mat>& v_af,
		double rangex[2], double rangey[2],
		cv::Mat& matV
	);
	int compose_images_backward_v2(
		std::vector<cv::Mat>& v_images,
		std::vector<cv::Mat>& v_af,
		double rangex[2], double rangey[2],
		cv::Mat& matV,
		double ratio_sigma
	);

	//	
	int compose_matP(
		std::vector<cv::Mat>& v_P_neighbor,
		cv::Size& sz0,
		std::vector<cv::Mat>& v_P_out,
		double rangex_out[2],
		double rangey_out[2],
		cv::Mat matEye
	);



	int update_link0(
		cv::Size& sz0,
		std::vector<cv::Mat>& v_P1,
		std::vector<cv::Point2f>& v_pt_out
	);
	int update_link(
		cv::Size& sz0,
		std::vector<cv::Mat>& v_P1,
		double rangex1[2], double rangey1[2],
		std::vector<int>& v_link,
		std::vector<cv::Point2f>& v_pt_out
	);

	//	�ǐՌo�H�̉���
	//		�S�̉摜�ɑ΂��铊�e�ϊ��s��̔z�񂪂����āA
	//		���ꂪ�ǐՏ��ɕ���ł��āA
	//		���e�ϊ��s��ɂ���ČX�̉摜���S�̉摜�Ƀ}�b�s���O����Ă���Ƃ��A
	//		�S�̉摜�̂Ȃ��ŌX�̉摜���S�����񂾂�A�ǐՌo�H�������ł���B
	int draw_trackingline(
		cv::Mat& matV,
		cv::Size& sz0,
		std::vector<cv::Mat>& v_P1,
		double rangex1[2], double rangey1[2]
	);
	int draw_trackingline(
		cv::Mat& matV,
		std::vector<cv::Point2f>& v_pt,
		std::vector<int>& vflag,
		double rangex1[2], double rangey1[2],
		std::vector<int>& v_link,
		cv::Scalar color_line
	);

};
