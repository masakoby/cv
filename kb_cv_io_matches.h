#include <vector>
#include <opencv2/opencv.hpp>

#pragma once

namespace kb
{
	int save_pt2d_pair(std::string& path, std::vector<cv::Point2f>& vec_pts1, std::vector<cv::Point2f>& vec_pts2);
	int load_pt2d_pair(std::string& path, std::vector<cv::Point2f>& vec_pts1, std::vector<cv::Point2f>& vec_pts2);
};
