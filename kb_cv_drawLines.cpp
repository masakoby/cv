#include "kb_cv_drawLines.h"

void kb::drawLines(
	cv::Mat& mat1,
	std::vector<cv::Point2f>& vp,
	cv::Scalar color,
	int thickness,
	int close)
{
	int num_vp = vp.size();
	for (int k = 0; k < num_vp; k++) {
		int k2 = (k + 1) % num_vp;
		cv::line(mat1, vp[k], vp[k2], color, thickness);
	}
}
