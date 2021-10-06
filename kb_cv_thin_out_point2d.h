#include <opencv2/opencv.hpp>

#pragma once

namespace kb
{
	//	２次元点群を間引く
	//		間引かれた後に、残った点群のインデックスを返す
	int thin_out_point2d(
		std::vector<cv::Point2f>& vpt_in,
		std::vector<int>& vidx_out,
		float width
	);
	//	
	int thin_out_point2d(
		std::vector<cv::Point2f>& vpt_in,
		std::vector<cv::Point2f>& vpt_out,
		float width
	);
};
