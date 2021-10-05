#include "kb_cv_drawContours.h"
#include "kb_color_palette.h"

//	
void kb::drawContours(
	cv::Mat& mat1,
	std::vector<std::vector<std::vector<cv::Point>>>& vv_contours,
	cv::Mat& matV,
	int thickness,
	double ratio_reduce	//	縮小倍率(0.1以下にすると、縮小機能オフ）
)
{
	mat1.copyTo(matV);

	int num_vv = vv_contours.size();
	for (int k = 0; k < num_vv; k++) {
		int idx = (k % 255) + 1;
		unsigned char rr, gg, bb;
		kb::random_color_palette(idx, &rr, &gg, &bb);

		int num_v = vv_contours[k].size();
		for (int kk = 0; kk < num_v; kk++) {
			int num_p = vv_contours[k][kk].size();
			for (int i = 0; i < num_p; i++) {
				int i2 = (i + 1) % num_p;
				cv::line(matV, vv_contours[k][kk][i], vv_contours[k][kk][i2], cv::Scalar(bb, gg, rr), thickness);
			}
		}
	}
}
