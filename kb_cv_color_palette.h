#include <opencv2/opencv.hpp>

#pragma once

namespace kb
{
	//	�p���b�g�̃o�[�쐬
	int palette_bar(cv::Mat& matRGB, int type);

	//	�p���b�g�̓Ǎ���
	int load_csv_palette(std::string& path, std::vector< cv::Scalar>& palette);
};
