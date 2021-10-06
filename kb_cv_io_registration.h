#include <vector>
#include <string>

#include <opencv2/opencv.hpp>

#pragma once

namespace kb
{
	//	�a���X���C�h�̈ʒu���킹�����c�[���ɓǂݍ��܂���Ή��_
	//	AAAA\1-AAAA_cpt.txt
	//	AAAA\2-AAAA_cpt.txt

	//	
	int save_corresponding_points(
		std::string& dname_output,
		std::string& filetitle,
		std::vector<cv::Point2f>& mp1,
		std::vector<cv::Point2f>& mp2,
		double base_ratio	//	�a���X���C�h�摜����S�̉摜�𓾂����̏k���{��
	);

	int load_corresponding_points(
		std::string& dname_output,
		std::string& filetitle,
		std::vector<cv::Point2f>& mp1,
		std::vector<cv::Point2f>& mp2
	);

};
