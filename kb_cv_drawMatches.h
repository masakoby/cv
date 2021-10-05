#include <vector>

#include <opencv2/opencv.hpp>

#pragma once

namespace kb
{
	//	対応点の可視化
	//		opencvの対応点可視化関数は、
	//		cv::KeyPointオブジェクトで受け渡す。
	//		２次元座標配列を渡して描画するように関数を作成した
	//		可視化の際、画像解像度を落とす機能も付加
	void drawMatches(
		cv::Mat& mat1,
		cv::Mat& mat2,
		std::vector<cv::Point2f>& mp1,
		std::vector<cv::Point2f>& mp2,
		cv::Mat& matV12,
		double ratio_reduce	//	縮小倍率(0.1以下にすると、縮小機能オフ）
		);

};
