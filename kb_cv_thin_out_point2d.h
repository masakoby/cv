#include <opencv2/opencv.hpp>

#pragma once

namespace kb
{
	//	�Q�����_�Q���Ԉ���
	//		�Ԉ����ꂽ��ɁA�c�����_�Q�̃C���f�b�N�X��Ԃ�
	int thin_out_point2d(
		std::vector<cv::Point2f>& vpt_in,
		std::vector<int>& vidx_out,
		float width
	);
	//	
	int thin_out_point2d(
		std::vector<cv::Point2f>& vpt_in,
		std::vector<cv::Point2f>& vpt_out,
		float width
	);
};
