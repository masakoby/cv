#include <vector>
#include <opencv2/opencv.hpp>

#pragma once

namespace kb
{
	//	矩形の４隅の点を取得する
	//		１周まわす形で得る
	void rect2points(cv::Rect& rect, std::vector<cv::Point2f>& vp);
};
