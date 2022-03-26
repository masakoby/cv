
#include <opencv2/opencv.hpp>
#include <vector>
#pragma once

namespace kb
{
	//	３次元座標の対応から、変換行列を求める
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
	//	３次元座標の対応から、変換行列を求める
	int calculate_mat4x4(
		std::vector< double >& v_temp1,
		std::vector< double >& v_temp2,
		double* mat4x4,
		double* ratio
	);

	//	対応点から、３次元の回転変換行列を求める
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