#include <opencv2/opencv.hpp>

#pragma once

namespace kb
{
	inline double length(cv::Point2f v)
	{
		return sqrt(v.x * v.x + v.y * v.y);
	}
};
