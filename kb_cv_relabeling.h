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


	//	領域間の距離閾値でラベル領域を結合する
	int relabeling_distance_between_regions(
		cv::Mat& matL1,
		int num_label1,
		cv::Mat& matL2,
		int dis1
	);

	//ラベル番号の間を詰める
	int relabeling_close_it_up(cv::Mat& matL1, cv::Mat& matL2);

	//	ラベル領域のエッジ領域を取り出す
	//		以前の関数名　labeling_edge
	int extract_edge_32S(cv::Mat& matL, cv::Mat& matL_out);

	//	ラベル領域を膨張させる
	int dilate_32S(
		cv::Mat& matL1,
		int num_label,
		cv::Mat& matL2,
		int num_max_iter,
		cv::Mat& mask0
	);

};
