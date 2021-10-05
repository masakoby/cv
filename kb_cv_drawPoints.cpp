#include "kb_cv_drawPoints.h"
#include "kb_cv_resize.h"

//
void kb::drawPoints(
	cv::Mat& mat1,
	cv::Mat& mat1_out,
	std::vector<cv::Point2f>& vp, 
	double ratio,
	int radius,
	cv::Scalar color)
{

	kb::resize(mat1, mat1_out, ratio);

	if (ratio > 0.0) {
		int num1 = vp.size();
		for (int k = 0; k < num1; k++) {
			cv::Point p1(vp[k].x * ratio, vp[k].y * ratio);
			cv::circle(mat1_out, p1, radius, color, radius / 2);
		}
	}
	else {
		int num1 = vp.size();
		for (int k = 0; k < num1; k++) {
			cv::Point p1 = vp[k];
			cv::circle(mat1_out, p1, radius, color, radius / 2);
		}
	}

}
