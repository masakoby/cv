#include <opencv2/opencv.hpp>

#pragma once

namespace kb
{
	//	マッチングの結果
	//	変換行列を指定してオーバーレイ
	//
	int pasteTo(
		cv::Mat& matBase,	//	
		cv::Mat& matOver,	//	
		cv::Mat& matP,		//	変換行列
		cv::Mat& matOut,	//	
		int mode			//	
	);
};
