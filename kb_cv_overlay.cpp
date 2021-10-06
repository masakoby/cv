#include "kb_cv_overlay.h"

void kb::overlay(cv::Mat& matVis, cv::Mat& mask, cv::Scalar color, double ratio)
{
	cv::Vec3b a;
	a[0] = color[0];
	a[1] = color[1];
	a[2] = color[2];

	cv::Size sz = matVis.size();
	cv::Size sz2 = mask.size();

	if (sz.width != sz2.width || sz.height != sz2.height)
		return;

	if (ratio < 0.0) {
		for (int j = 0; j < sz.height; j++) {
			for (int i = 0; i < sz.width; i++) {
				if (mask.at<unsigned char>(j, i) == 0)
					continue;
				matVis.at<cv::Vec3b>(j, i) = a;
			}
		}
	}
	else {
		double r2 = ratio;
		if (r2 > 1.0) {
			r2 = 1.0;
		}
		double r1 = 1.0 - r2;

		a[0] = color[0]*r1;
		a[1] = color[1]*r1;
		a[2] = color[2]*r1;
		cv::Vec3b a3;

		for (int j = 0; j < sz.height; j++) {
			for (int i = 0; i < sz.width; i++) {
				if (mask.at<unsigned char>(j, i) == 0)
					continue;

				cv::Vec3b a2 = matVis.at<cv::Vec3b>(j, i);
				a3[0] = a2[0] * r2 + a[0];
				a3[1] = a2[1] * r2 + a[1];
				a3[2] = a2[2] * r2 + a[2];
				matVis.at<cv::Vec3b>(j, i) = a3;
			}
		}
	}
}

void kb::overlayRGB(cv::Mat& matVis, cv::Mat& maskRGB, double ratio)
{
	cv::Size sz = matVis.size();
	cv::Size sz2 = maskRGB.size();
	if (sz.width != sz2.width || sz.height != sz2.height)
		return;

	if (ratio < 0.0) {
		for (int j = 0; j < sz.height; j++) {
			for (int i = 0; i < sz.width; i++) {
				cv::Vec3b a = maskRGB.at<cv::Vec3b>(j, i);
				if (a[0] == 0 && a[1] == 0 && a[2] == 0)
					continue;

				matVis.at<cv::Vec3b>(j, i) = a;
			}
		}
	}
	else {
		double r2 = ratio;
		if (r2 > 1.0) {
			r2 = 1.0;
		}
		double r1 = 1.0 - r2;
		cv::Vec3b a3;

		for (int j = 0; j < sz.height; j++) {
			for (int i = 0; i < sz.width; i++) {
				cv::Vec3b a = maskRGB.at<cv::Vec3b>(j, i);
				if (a[0] == 0 && a[1] == 0 && a[2] == 0)
					continue;

				cv::Vec3b a2 = matVis.at<cv::Vec3b>(j, i);
				a3[0] = a[0] * r1 + a2[0] * r2;
				a3[1] = a[1] * r1 + a2[1] * r2;
				a3[2] = a[2] * r1 + a2[2] * r2;

				matVis.at<cv::Vec3b>(j, i) = a3;
			}
		}
	}
}

