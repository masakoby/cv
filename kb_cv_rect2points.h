#include <vector>
#include <opencv2/opencv.hpp>

#pragma once

namespace kb
{
	//	‹éŒ`‚Ì‚S‹÷‚Ì“_‚ðŽæ“¾‚·‚é
	//		‚PŽü‚Ü‚í‚·Œ`‚Å“¾‚é
	void rect2points(cv::Rect& rect, std::vector<cv::Point2f>& vp);
};
