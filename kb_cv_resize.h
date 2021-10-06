#include <opencv2/opencv.hpp>

#pragma once

namespace kb
{
	//	opencv��cv::resize()�֐��Ăяo��
	//	 �摜�k���F���A���Ή�
	// �@�摜�g��F�R���֐����
	//	 ratio<0.01: �R�s�[
	int resize(cv::Mat& mat1, cv::Mat& mat_out, double ratio);

	//	�o�͉摜�T�C�Y���Œ�ɂ���
	//	 �摜�k���F���A���Ή�
	// �@�摜�g��F�R���֐����
	//	
	int resize(cv::Mat& mat1, cv::Mat& mat_out, cv::Size& sz_out);

	//	���W�l�ɔ{�����|����
	//	 ratio<0.0: �R�s�[
	int resize(std::vector<cv::Point2f>& mp1, std::vector<cv::Point2f>& mp1_out, double ratio);


	//	���W�l�ɔ{�����|����
	//	 ratio<0.0: �R�s�[
	void resize(cv::Rect& rect1, cv::Rect& rect1_out, double ratio);

};
