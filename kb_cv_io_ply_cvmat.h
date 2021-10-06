#include <string>
#include <vector>

#include <opencv2/opencv.hpp>

#pragma once

namespace kb
{
	int save_Mat_8UC3_as_edge_ply(std::string& path, cv::Mat& mat);
	int save_Mat_8UC3_as_quadrilateral_mesh_ply(std::string& path, cv::Mat& mat);
	int save_Mat_8UC3_as_quadrilateral_mesh_ply(std::string& path, cv::Mat& mat, cv::Mat& matDepth, double dx, double dy, int mode_normal);

};
