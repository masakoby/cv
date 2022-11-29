#include <opencv2/opencv.hpp>
#include <vector>

#pragma once

namespace kb
{
	//	同じ画像サイズの画像を縦横に並べて、１枚の大きな画像にする関数
	void arrange_matN(std::vector<cv::Mat>& vec_mat, cv::Mat& matV, int num_width = -1);
	void arrange_matN_subset(std::vector<cv::Mat>& vec_mat, cv::Mat& matV, int num_width, int start_idx, int num_mat);

	//	異なる画像サイズの配列に対して、タイリングして１枚の大きな画像にする関数
	int arrange_matN(std::vector<cv::Mat>& vec_mat, cv::Mat& matV, int nx, int ny, int width_tile);


	void arrange_mat2(cv::Mat& mat1, cv::Mat& mat2, cv::Mat& matV);

};
