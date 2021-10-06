#include <vector>

#include <opencv2/opencv.hpp>

#pragma once

namespace kb
{
	//	s—ñ‚ÌŠ|‚¯Z
	//	cv::Mat * cv::Point2f
	int matmul_3x3(cv::Mat& matAf_64F, std::vector<cv::Point2f>& vp, std::vector<cv::Point2f>& vp_out);
	int matmul_3x3(cv::Mat& matAf_64F, cv::Point2f& p, cv::Point2f& p_out);

	//	“¯À•W
	int homogeneous_transformation_3x3(cv::Mat& matAf_64F, std::vector<cv::Point2f>& vp, std::vector<cv::Point2f>& vp_out);
	int homogeneous_transformation_3x3(cv::Mat& matAf_64F, cv::Point2f& p, cv::Point2f& p_out);

};