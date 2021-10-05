#include "kb_cv_histogram.h"

int kb::histogram256_32F(cv::Mat& mat32F, std::vector<float>& hist, float step)
{
	int nbin = (int)((255.0 + step * 0.5) / step);

	hist.resize(nbin, 0.0);

	cv::Size sz1 = mat32F.size();
	for (int j = 0; j < sz1.height; j++) {
		for (int i = 0; i < sz1.width; i++) {
			int idx = (int)(mat32F.at<float>(j, i) / step);
			if (idx < 0) { idx = 0; }
			else if (nbin <= idx) { idx = nbin - 1; }
			hist[idx] += 1.0;
		}
	}

	return 0;
}

int kb::histogram256_32F(cv::Mat& mat32F, cv::Mat& hist32F, float step)
{
	int nbin = (int)((255.0 + step * 0.5) / step);

	hist32F = cv::Mat(1, nbin, CV_32F, cv::Scalar(0));

	cv::Size sz1 = mat32F.size();
	for (int j = 0; j < sz1.height; j++) {
		for (int i = 0; i < sz1.width; i++) {
			int idx = (int)(mat32F.at<float>(j, i) / step);
			if (idx < 0) { idx = 0; }
			else if (nbin <= idx) { idx = nbin - 1; }
			hist32F.at<float>(idx) += 1.0;
		}
	}

	return 0;
}

int kb::histogram256_32F(cv::Mat& mat32F, std::vector<float>& hist)
{
	int nbin = 256;
	hist.resize(nbin, 0.0);

	cv::Size sz1 = mat32F.size();
	for (int j = 0; j < sz1.height; j++) {
		for (int i = 0; i < sz1.width; i++) {
			int idx = (int)(mat32F.at<float>(j, i) + 0.5);
			if (idx < 0) { idx = 0; }
			else if (nbin <= idx) { idx = nbin - 1; }
			hist[idx] += 1.0;
		}
	}

	return 0;
}

int kb::histogram256_32F(cv::Mat& mat32F, cv::Mat& hist32F)
{
	int nbin = 256;
	hist32F = cv::Mat(1, nbin, CV_32F, cv::Scalar(0));

	cv::Size sz1 = mat32F.size();
	for (int j = 0; j < sz1.height; j++) {
		for (int i = 0; i < sz1.width; i++) {
			int idx = (int)(mat32F.at<float>(j, i) + 0.5);
			if (idx < 0) { idx = 0; }
			else if (nbin <= idx) { idx = nbin - 1; }
			hist32F.at<float>(idx) += 1.0;
		}
	}

	return 0;
}
