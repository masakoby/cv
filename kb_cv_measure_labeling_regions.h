#include <opencv2/opencv.hpp>

#include <vector>

#pragma once

namespace kb
{

	//	面積
	int measureSquare(
		cv::Mat& matLabel,
		int numLabel,
		std::vector<int>& oVec
	);

	//	重心
	int measureBarycenter(
		cv::Mat& matLabel,
		int numLabel,
		std::vector<int>& vecSquare,
		std::vector<double>& vecPos
	);

	//	平均輝度
	int measureAverage_RGB(
		cv::Mat& matLabel,
		int numLabel,
		cv::Mat& matValueRGB,
		std::vector<int>& vecSquare,
		std::vector<double>& vecAverageRGB
	);
	//	平均輝度と分散
	int measureAverageVariance_RGB(
		cv::Mat& matLabel,
		int numLabel,
		cv::Mat& matValueRGB,
		std::vector<int>& vecSquare,
		std::vector<double>& vecAverage,
		std::vector<double>& vecVariance
	);

	//	バウンディングボックス
	int measureBoundingBox(
		cv::Mat& matL1, int num_label,
		std::vector<int>& squares,
		std::vector<cv::Point>& vecPtsMin,
		std::vector<cv::Point>& vecPtsMax
	);

	//	バウンディングボックス（斜め）
	int measureBoundingBox_by_PCA(
		cv::Mat& matL1, int num_label,
		std::vector<cv::Point2f>& v_pos,// 重心
		std::vector<cv::Point2f>& v_dir,// 領域の主軸方向
		std::vector<cv::Point2f>& v_pos2,//　主軸方向における重心からの最遠位置（ラベル数×２）
		std::vector<cv::Point2f>& v_pos4//バウンディングボックス（ラベル数×４）
	);

	//	ラベル領域ごとの３次元ヒストグラム取得
	int measureHistogram3D_RGB(
		cv::Mat& matLabel,
		int numLabel,
		cv::Mat& matValueRGB,
		int num_bin,//histogramのビン数
		std::vector<float>& hist
	);

	//	ラベル領域間の距離を計測
	int measureMinimumDistance(
		cv::Mat& matLabel,
		int numLabel,
		std::vector<float>& oVec	//	ラベル数×ラベル数

	);

	int measureContours(
		cv::Mat& matLabel,
		int numLabel,
		std::vector<std::vector<std::vector<cv::Point>>>& vv_contours
		);

};
