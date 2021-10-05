#include "kb_cv_drawMargin.h"

//	
void kb::drawMargin(
	cv::Mat& mat8UC3,
	cv::Vec3b a,
	int thickness
)
{
	cv::Size sz = mat8UC3.size();
	for (int j = 0; j < thickness; j++) {
		for (int i = 0; i < sz.width; i++) {
			mat8UC3.at<cv::Vec3b>(j, i) = a;
		}
	}
	for (int j = sz.height-thickness; j < sz.height; j++) {
		for (int i = 0; i < sz.width; i++) {
			mat8UC3.at<cv::Vec3b>(j, i) = a;
		}
	}
	for (int j = 0; j < sz.height; j++) {
		for (int i = 0; i < thickness; i++) {
			mat8UC3.at<cv::Vec3b>(j, i) = a;
		}
	}
	for (int j = 0; j < sz.height; j++) {
		for (int i = sz.width-thickness; i < sz.width; i++) {
			mat8UC3.at<cv::Vec3b>(j, i) = a;
		}
	}
}
