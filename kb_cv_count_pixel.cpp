#include "kb_cv_count_pixel.h"

int kb::count_pixel_non_zero(cv::Mat& mat8U)
{
	cv::Size sz = mat8U.size();
	if (sz.width <= 0 || sz.height <= 0)
		return -1;

	int cnt = 0;
	for (int j = 0; j < sz.height; j++) {
		for (int i = 0; i < sz.width; i++) {
			if (mat8U.at<unsigned char>(j, i) > 0)
				cnt++;
		}
	}
	return cnt;
}

int kb::count_pixel_non_zero(cv::Mat& mat8U, int x0, int y0, int width, int height)
{
	cv::Size sz = mat8U.size();
	if (sz.width <= 0 || sz.height <= 0)
		return -1;

	int x0_end = x0 + width;
	int y0_end = y0 + height;

	if (x0 < 0) {
		x0 = 0;
	}
	if (y0 < 0) {
		y0 = 0;
	}
	if (sz.width < x0_end) {
		x0_end = sz.width;
	}
	if (sz.height < y0_end) {
		y0_end = sz.height;
	}

	int cnt = 0;
	for (int j = y0; j < y0_end; j++) {
		for (int i = x0; i < x0_end; i++) {
			if (mat8U.at<unsigned char>(j, i) > 0)
				cnt++;
		}
	}
	return cnt;
}

int kb::count_pixel_non_zero(cv::Mat& mat8U, int x0, int y0, int width, int height, std::vector<int>& hist)
{
	cv::Size sz = mat8U.size();
	if (sz.width <= 0 || sz.height <= 0)
		return -1;

	int x0_end = x0 + width;
	int y0_end = y0 + height;

	if (x0 < 0) {
		x0 = 0;
	}
	if (y0 < 0) {
		y0 = 0;
	}
	if (sz.width < x0_end) {
		x0_end = sz.width;
	}
	if (sz.height < y0_end) {
		y0_end = sz.height;
	}

	hist.resize(256, 0);
	for (int j = y0; j < y0_end; j++) {
		for (int i = x0; i < x0_end; i++) {
			if (mat8U.at<unsigned char>(j, i) > 0) {
				hist[mat8U.at<unsigned char>(j, i)]++;
			}
		}
	}

	int max_cnt = 0;
	int idx = 0;
	for (int i = 1; i < 256; i++) {
		if (hist[i] > max_cnt) {
			max_cnt = hist[i];
			idx = i;
		}
	}
	return idx;
}




int kb::count_pixel_Saturation(cv::Mat& matRGB, int threshold_Sat)
{
	cv::Mat matHSV;
	cv::cvtColor(matRGB, matHSV, cv::COLOR_BGR2HSV);
	cv::Size sz = matHSV.size();
	int cnt = 0;
	for (int j = 0; j < sz.height; j++) {
		for (int i = 0; i < sz.width; i++) {
			if (matHSV.at<cv::Vec3b>(j, i)[1] > threshold_Sat) {
				cnt++;
			}
		}
	}
	return cnt;
}

//	エッジのピクセル数をカウントする
int kb::count_pixel_Edge(cv::Mat& mat8U, int threshold_Edge)
{
	cv::Size sz = mat8U.size();
	cv::Mat matLap;
	cv::Laplacian(mat8U, matLap, -1);

	//cv::Mat matTh(sz,CV_8U, cv::Scalar(0));

	int cnt = 0;
	for (int j = 0; j < sz.height; j++) {
		for (int i = 0; i < sz.width; i++) {
			if (matLap.at<unsigned char>(j, i) > threshold_Edge) {
				cnt++;
				//matTh.at<unsigned char>(j, i) = 255;
			}
		}
	}
	//cv::namedWindow("laplacian", cv::WINDOW_NORMAL);
	//cv::imshow("laplacian", matTh);

	return cnt;
}
