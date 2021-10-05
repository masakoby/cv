#include "kb_cv_cvtColor.h"

int kb::RGB2Lum_32F(cv::Mat& matRGB, cv::Mat& mat32F)
{
	cv::Size sz1 = matRGB.size();
	mat32F = cv::Mat(sz1, CV_32F);
	for (int j = 0; j < sz1.height; j++) {
		for (int i = 0; i < sz1.width; i++) {
			cv::Vec3b a = matRGB.at<cv::Vec3b>(j, i);
			mat32F.at<float>(j, i) = (float)a[2] * 0.299 + (float)a[1] * 0.587 + (float)a[0] * 0.114;
		}
	}

	return 0;
}
