
#include <opencv2/opencv.hpp>
#include <vector>

#pragma once

namespace kb
{
	//
	//	�摜�̋P�x�������Ƃ��ă��b�V���f�[�^���\�z����
	//	
	int cvmat2mesh(
		cv::Mat& mat8U,
		std::vector<float>& v3d,
		std::vector<int>& vidx,
		float max_value = 100.0
	);
	int cvmat2mesh_64F(
		cv::Mat& mat64F,
		std::vector<float>& v3d,
		std::vector<int>& vidx
	);
};
