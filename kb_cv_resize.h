#include <opencv2/opencv.hpp>

#pragma once

namespace kb
{
	//	opencvのcv::resize()関数呼び出し
	//	 画像縮小：モアレ対応
	// 　画像拡大：３次関数補間
	//	 ratio<0.01: コピー
	int resize(cv::Mat& mat1, cv::Mat& mat_out, double ratio);

	//	出力画像サイズを固定にする
	//	 画像縮小：モアレ対応
	// 　画像拡大：３次関数補間
	//	
	int resize(cv::Mat& mat1, cv::Mat& mat_out, cv::Size& sz_out);

	//	座標値に倍率を掛ける
	//	 ratio<0.0: コピー
	int resize(std::vector<cv::Point2f>& mp1, std::vector<cv::Point2f>& mp1_out, double ratio);


	//	座標値に倍率を掛ける
	//	 ratio<0.0: コピー
	void resize(cv::Rect& rect1, cv::Rect& rect1_out, double ratio);

};
