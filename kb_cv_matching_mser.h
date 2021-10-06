#include <vector>

#include <opencv2/opencv.hpp>

#pragma once

namespace kb
{

	int match_MSER(
		cv::Mat& mat1,
		cv::Mat& mat2,
		std::vector<cv::DMatch>& v_dm,
		std::vector<cv::KeyPoint>& v_kp1,
		std::vector<cv::KeyPoint>& v_kp2,
		int delta, //5
		int min_area, //60
		int max_area,//14400
		double max_variation,//0.25
		double min_div,//0.2
		int max_ev,//200
		double area_thres,//1.01
		double min_margin,//0.003
		int edge_blur_size//5
	);

};
