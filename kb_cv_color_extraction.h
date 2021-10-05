#include <opencv2/opencv.hpp>

#pragma once

namespace kb
{
	//	色抽出
	//		彩度 s=(0,255)の閾値
	//		色相 h=(0,180)の閾値２つ
	//		s>thresS1 and
	//		  thresH1<h<thresH2, if thresH1<thresH2
	//		  h<thresH1 or thresH2<h, if thresH2<thresH1
	//		  all, if thresH1<0 or thresH2<0
	//
	//	茶色抽出
	//		thresS1=70
	//		thresH1=160
	//		thresH2=20
	//
	inline int color_extraction(
		cv::Mat& matRGB,
		cv::Mat& mat8U_out, 
		int thresS1,
		int thresH1, 
		int thresH2
	)
	{
		cv::Mat matHSV;
		cv::cvtColor(matRGB, matHSV, cv::COLOR_BGR2HSV);
		cv::Size sz = matHSV.size();
		mat8U_out = cv::Mat(sz, CV_8UC1, cv::Scalar(0));

		unsigned char b2 = 255;

		if (thresH1 < 0 || thresH2 < 0) {
			for (int j = 0; j < sz.height; j++) {
				for (int i = 0; i < sz.width; i++) {
					cv::Vec3b a = matHSV.at<cv::Vec3b>(j, i);
					if (a[1] > thresS1) {
						mat8U_out.at<unsigned char>(j, i) = b2;
					}
				}
			}
		}
		else if (thresH1 <= thresH2) {
			for (int j = 0; j < sz.height; j++) {
				for (int i = 0; i < sz.width; i++) {
					cv::Vec3b a = matHSV.at<cv::Vec3b>(j, i);
					if (a[1] > thresS1 && thresH1 < a[0] && a[0] < thresH2) {
						mat8U_out.at<unsigned char>(j, i) = b2;
					}
				}
			}
		}
		else {
			for (int j = 0; j < sz.height; j++) {
				for (int i = 0; i < sz.width; i++) {
					cv::Vec3b a = matHSV.at<cv::Vec3b>(j, i);
					if (a[1] > thresS1 && (thresH1 < a[0] || a[0] < thresH2)) {
						mat8U_out.at<unsigned char>(j, i) = b2;
					}
				}
			}
		}
		return 0;
	}
};
