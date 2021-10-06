#include "kb_cv_rect2points.h"

void kb::rect2points(cv::Rect& rect, std::vector<cv::Point2f>& vp)
{
	vp.push_back(cv::Point2f(rect.x, rect.y));
	vp.push_back(cv::Point2f(rect.x + rect.width, rect.y));
	vp.push_back(cv::Point2f(rect.x + rect.width, rect.y + rect.height));
	vp.push_back(cv::Point2f(rect.x, rect.y + rect.height));
}
