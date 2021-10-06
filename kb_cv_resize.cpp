#include "kb_cv_resize.h"


int kb::resize(cv::Mat& mat1, cv::Mat& mat_out, cv::Size& sz_out)
{
	cv::Size sz1 = mat1.size();
	cv::Size sz2 = sz_out;

	if (sz2.width<=0 ||  sz2.height<=0) {
		mat1.copyTo(mat_out);
	}
	else {
		if (sz1.width > sz2.width) {
			//	ƒ‚ƒAƒŒ‘Î‰ž
			cv::resize(mat1, mat_out, sz2, 0, 0, cv::INTER_AREA);
		}
		else {
			//	‚RŽŸ•âŠÔ
			cv::resize(mat1, mat_out, sz2, 0, 0, cv::INTER_CUBIC);
		}
	}

	return 0;
}

int kb::resize(cv::Mat& mat1, cv::Mat& mat_out, double ratio)
{
	cv::Size sz1 = mat1.size();
	cv::Size sz2(sz1.width * ratio, sz1.height * ratio);

	if (ratio < 0.01) {
		mat1.copyTo(mat_out);
	}else{
		if (ratio < 1.0) {
			//	ƒ‚ƒAƒŒ‘Î‰ž
			cv::resize(mat1, mat_out, sz2, 0, 0, cv::INTER_AREA);
		}
		else {
			//	‚RŽŸ•âŠÔ
			cv::resize(mat1, mat_out, sz2, 0, 0, cv::INTER_CUBIC);
		}
	}

	return 0;
}

//	À•W’l‚É”{—¦‚ðŠ|‚¯‚é
int kb::resize(std::vector<cv::Point2f>& mp1, std::vector<cv::Point2f>& mp1_out, double ratio)
{
	if (ratio > 0.0) {
		int num1 = mp1.size();
		mp1_out.resize(num1);
		for (int i = 0; i < num1; i++) {
			mp1_out[i].x = mp1[i].x * ratio;
			mp1_out[i].y = mp1[i].y * ratio;
		}
	}
	else {
		mp1_out = mp1;
	}
	return 0;
}

//	À•W’l‚É”{—¦‚ðŠ|‚¯‚é
//	 ratio<0.0: ƒRƒs[
void kb::resize(cv::Rect& rect1, cv::Rect& rect1_out, double ratio)
{
	if (ratio > 0.0) {
		rect1_out.x = rect1.x * ratio;
		rect1_out.y = rect1.y * ratio;
		rect1_out.width = rect1.width * ratio;
		rect1_out.height = rect1.height * ratio;
	}
	else {
		rect1_out = rect1;
	}
}
