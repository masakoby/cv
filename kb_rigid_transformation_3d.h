
#include <opencv2/opencv.hpp>
#include <vector>
#pragma once

namespace kb
{
	//	�R�������W�̑Ή�����A�ϊ��s������߂�
	int calculate_mat4x4(
		std::vector< double >& v_temp1,
		std::vector< double >& v_temp2,
		double* mat4x4
	);
	int calculate_mat4x4(
		std::vector< cv::Point3f >& v_temp1,
		std::vector< cv::Point3f >& v_temp2,
		double* mat4x4
	);
	//	�R�������W�̑Ή�����A�ϊ��s������߂�
	int calculate_mat4x4(
		std::vector< double >& v_temp1,
		std::vector< double >& v_temp2,
		double* mat4x4,
		double* ratio
	);

	//	�Ή��_����A�R�����̉�]�ϊ��s������߂�
	int calculate_matR3x3(
		std::vector< double >& v_temp1,
		std::vector< double >& v_temp2,
		double* mat3x3
	);

	int calculate_mat4x4_with_constrained_point(
		std::vector< double >& v_temp1,
		std::vector< double >& v_temp2,
		double* mat4x4
	);

};