

#include <vector>
#include <string>

#include <opencv2/opencv.hpp>

#pragma once

namespace kb
{

	//	2d points 
	int save_pt2d(std::string& path, std::vector<cv::Point2f>& vec_pts);
	int load_pt2d(std::string& path, std::vector<cv::Point2f>& vec_pts);

	//	3d points 
	int save_pt3d(std::string& path, std::vector<cv::Point3f>& vec_pts);
	int load_pt3d(std::string& path, std::vector<cv::Point3f>& vec_pts);


	int save_pt2d_csv(std::string& path, std::vector<double>& vec_pts);
	int save_ptNd_csv(std::string& path, std::vector<double>& vec_pts, int dim);


	//	2d line 
	int save_line2d(std::string& path, std::vector<double>& vec_pts);
	int load_line2d(std::string& path, std::vector<double>& vec_pts);
	int load_line2d(std::string& path, std::vector<cv::Point2f>& vec_pts);


	//	3d line 
	int save_line3d(std::string& path, std::vector<double>& vec_pts);
	int load_line3d(std::string& path, std::vector<double>& vec_pts);

	//	1d index
	int save_vec_index(std::string& path, std::vector<int>& vec_index);
	int load_vec_index(std::string& path, std::vector<int>& vec_index);


	//
	int save_pt3d_as_ply(std::string& path, std::vector<cv::Point3d>& pts);
	int save_pt3d_as_ply(std::string& path, std::vector<cv::Point3f>& pts);
};
