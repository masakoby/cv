#include <opencv2/opencv.hpp>
#include <vector>

#pragma once

namespace kb
{
	int relabeling_8n(
		cv::Mat& matL1,
		cv::Mat& matL2,
		int del = 0
	);
	int relabeling_4n(
		cv::Mat& matL1,
		int num_label1,
		cv::Mat& matL2,
		int del
	);


	//	�̈�Ԃ̋���臒l�Ń��x���̈����������
	int relabeling_distance_between_regions(
		cv::Mat& matL1,
		int num_label1,
		cv::Mat& matL2,
		int dis1
	);

	//���x���ԍ��̊Ԃ��l�߂�
	int relabeling_close_it_up(cv::Mat& matL1, cv::Mat& matL2);

	//	���x���̈�̃G�b�W�̈�����o��
	//		�ȑO�̊֐����@labeling_edge
	int extract_edge_32S(cv::Mat& matL, cv::Mat& matL_out);

	//	���x���̈��c��������
	int dilate_32S(
		cv::Mat& matL1,
		int num_label,
		cv::Mat& matL2,
		int num_max_iter,
		cv::Mat& mask0
	);

};
