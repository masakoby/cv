#include <vector>
#include <string>

#pragma once

namespace kb
{
	//	1d points
	int load_pt1d(std::string& path, std::vector<double>& vec_pts);
	int save_pt1d(std::string& path, std::vector<double>& vec_pts, int precision = 0);

	//	2d points
	int save_pt2d(std::string& path, std::vector<float>& vec_pts);
	int load_pt2d(std::string& path, std::vector<float>& vec_pts);
	int save_pt2d(std::string& path, std::vector<double>& vec_pts);
	int load_pt2d(std::string& path, std::vector<double>& vec_pts);

	//	3d points
	int save_pt3d(std::string& path, std::vector<float>& vec_pts);
	int load_pt3d(std::string& path, std::vector<float>& vec_pts);
	int save_pt3d(std::string& path, std::vector<double>& vec_pts);
	int load_pt3d(std::string& path, std::vector<double>& vec_pts);

	//	Nd points
	int save_ptNd(std::string& path, std::vector<double>& vec_pts, int dim);
	int load_ptNd(std::string& path, std::vector<double>& vec_pts);
};
