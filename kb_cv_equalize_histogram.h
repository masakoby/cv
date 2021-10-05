#include <opencv2/opencv.hpp>

#pragma once

namespace kb {
	int equalizeHistForRGB2(
		cv::Mat& matRGB,
		cv::Mat& matRGB_out,
		float step_hist = 1.0,
		double ratio_sigma = 0.1,
		int window_size = 80,
		int window_step = 20,
		int num_thread = 10,
		int flag_sm = 0,
		double sigma = 2,
		double sat_ratio = 3.0
	);
	int equalizeHist(
		cv::Mat& matF,
		cv::Mat& matF_out,
		float step_hist,//=1.0, 
		double ratio_sigma,//=0.1, 
		int window_size,//=80, 
		int window_step,//=20,
		int num_thread//=1
	);

	int equalizeHistForRGB(
		cv::Mat& matRGB,
		cv::Mat& matRGB_out,
		float step, 
		int flag_sm,
		double sigma,
		double sat_ratio
	);

	int equalizeHist_32F(
		cv::Mat& mat32F, //	CV_32F
		cv::Mat& mat32F_out, //	CV_32F
		float step);

	int equalizeHist_32F(
		cv::Mat& mat32F, //	CV_32F
		cv::Mat& mat32F_out //	CV_32F
		);

};
