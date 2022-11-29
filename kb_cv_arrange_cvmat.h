#include <opencv2/opencv.hpp>
#include <vector>

#pragma once

namespace kb
{
	//	�����摜�T�C�Y�̉摜���c���ɕ��ׂāA�P���̑傫�ȉ摜�ɂ���֐�
	void arrange_matN(std::vector<cv::Mat>& vec_mat, cv::Mat& matV, int num_width = -1);
	void arrange_matN_subset(std::vector<cv::Mat>& vec_mat, cv::Mat& matV, int num_width, int start_idx, int num_mat);

	//	�قȂ�摜�T�C�Y�̔z��ɑ΂��āA�^�C�����O���ĂP���̑傫�ȉ摜�ɂ���֐�
	int arrange_matN(std::vector<cv::Mat>& vec_mat, cv::Mat& matV, int nx, int ny, int width_tile);


	void arrange_mat2(cv::Mat& mat1, cv::Mat& mat2, cv::Mat& matV);

};
