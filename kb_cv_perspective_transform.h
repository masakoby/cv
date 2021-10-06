#include <vector>
#include <opencv2/opencv.hpp>

#pragma once

namespace kb
{
	//	投影変換行列の逆行列を計算する
	int inversePerspectiveTransform(
		cv::Mat& matP, //	投影変換行列
		cv::Size& sz1, //	画像サイズ
		cv::Mat& matP_inv,
		cv::Point2f pt_range[2]
	);

	int updateRangePerspectiveTransform(
		std::vector<cv::Mat>& v_P,
		cv::Size& sz0,
		double rangex_out[2],
		double rangey_out[2]
	);

	//	投影変換行列によって、画像端座標のマッピング先の最大最小を更新する
	int updateRangePerspectiveTransform(
		cv::Mat& matP, cv::Size& sz0,
		double rangex[2], double rangey[2]);

	int calcPerspectiveTransform(
		cv::Point2f& pt,
		std::vector<cv::Mat>& v_P1,
		std::vector<cv::Point2f>& v_pt_out
	);

	int forward_P(
		cv::Mat& matP_bf,
		cv::Mat& matP_in,
		cv::Mat& matP_out,
		cv::Size& sz0
	);

};
