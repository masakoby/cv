#include <opencv2/opencv.hpp>

#pragma once

namespace kb
{
	int segmentation_by_kmeans_RGB(cv::Mat& matRGB, cv::Mat& matOut32S, int num_cluster, cv::Mat mask);
	int segmentation_by_kmeans_Gray(cv::Mat& matRGB, cv::Mat& matOut32S, int num_cluster, cv::Mat mask);
	int segmentation_by_kmeans_HSV(cv::Mat& matRGB, cv::Mat& matOut32S, int num_cluster, cv::Mat mask);

	//
	int remove_background_region(cv::Mat& mat32S, int num_label, cv::Mat& matRGB, cv::Scalar bk_color, cv::Mat& mat8U);
};
