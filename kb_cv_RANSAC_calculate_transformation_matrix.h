#include <vector>

#include <opencv2/opencv.hpp>

#pragma once

namespace kb
{
	//	RANSAC�ɂ��ϊ��s����v�Z����
	//		��������������ƂO�ȏオ�o�͂����
	//		�A�t�B���ϊ��s�񂪌v�Z�ł��Ȃ������Ƃ��A�|1��Ԃ��B
	//
	//	  �A�t�B���ϊ��s��(2x3)���v�Z����
	//�@	  r11 r12 t1
	//	�@�@  r21 r22 t2
	//		�o�͂�3x3�}�g���b�N�X�ƂȂ�
	//
	//		�������e�ϊ��s����g�ݍ���ł��邪�A���؂͏\���ɂ��Ă��Ȃ��̂�
	//		���̎�Ԃ�������
	int calculate_transformation_matrix_by_RANSAC(
		std::vector<cv::Point2f>& mp1,
		std::vector<cv::Point2f>& mp2,
		cv::Size& sz_img,			//	�摜�T�C�Y
		cv::Mat& matAf,				//	�v�Z���ʂ�3x3�s��
		std::vector<cv::Point2f>& mp1_inlier,
		std::vector<cv::Point2f>& mp2_inlier,
		double threshold_dis1,					//	�Ή��_��v����Ƃ݂Ȃ�����
		int thres_max_valid_cnt,				//	�Ή��_��v����ŏ���
		int RANSAC_iter_num,					//	RANSAC���s��
		int numThread,							//	�}���`�X���b�h
		double det_min,							//	�A�t�B���ϊ��s���2x2������determinant�l�̐���
		double det_max,							//	�A�t�B���ϊ��s���2x2������determinant�l�̐���	
		double ratio_area,						//	�摜�̒��S�t�߂̑Ή��_��D��I�Ɏg�p���邽�߂̌W��
												//	�@1.0 ���Ƃ��ׂĂ̓_���ϓ��Ɏg�p����
		double threshold_ratio_delta_center,	//	�摜���S�̈ړ�������臒l�ݒ�(-1����臒l�̋@�\�I�t)
		double threshold_angle,					//	��]�p�x��臒l(-1����臒l�̋@�\�I�t)
		int mode								//    0: affine transfromation
												// else: perspective transformation
	);

	class CParam_calculate_transformation_matrix_by_RANSAC
	{
	public:
		CParam_calculate_transformation_matrix_by_RANSAC()
		{

		}
		double threshold_dis1;					//	�Ή��_��v����Ƃ݂Ȃ�����
		int thres_max_valid_cnt;				//	�Ή��_��v����ŏ���
		int RANSAC_iter_num;					//	RANSAC���s��
		int numThread;							//	�}���`�X���b�h
		double det_min;							//	�A�t�B���ϊ��s���2x2������determinant�l�̐���
		double det_max;							//	�A�t�B���ϊ��s���2x2������determinant�l�̐���	
		double ratio_area;						//	�摜�̒��S�t�߂̑Ή��_��D��I�Ɏg�p���邽�߂̌W��
												//	�@1.0 ���Ƃ��ׂĂ̓_���ϓ��Ɏg�p����
		double threshold_ratio_delta_center;	//	�摜���S�̈ړ�������臒l�ݒ�(-1����臒l�̋@�\�I�t)
		double threshold_angle;					//	��]�p�x��臒l(-1����臒l�̋@�\�I�t)
		int mode;								//    0: affine transfromation
												// else: perspective transformation

	};
};
