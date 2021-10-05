#include <opencv2/opencv.hpp>

#pragma once

namespace kb
{
	//	領域がはみ出てもコピーする
	int copyTo_8UC3(cv::Mat& mat1, cv::Rect& rect, cv::Mat& mat2, cv::Vec3b bk);

	//	マスク領域のみコピーする
	//	領域がはみ出てもコピーする
	int copyTo_8UC3(cv::Mat& mat1, cv::Rect& rect, cv::Mat& mask, cv::Mat& mat2, cv::Vec3b bk);


	//
	//	全体画像からROIを切り出す。領域がはみ出てもコピーする
	//	
	int copyTo_8UC1(cv::Mat& mat1, cv::Rect& rect1, cv::Mat& mat2);

	//
	//	小さいROI画像を全体画像へ張り付けるときに用いる
	//	
	int copyTo_8UC1(cv::Mat& mat1, cv::Mat& mask1, cv::Mat& mat2, cv::Point& pt2);

};
