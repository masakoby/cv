#include <fstream>

#include "kb_io_points.h"

int kb::save_pt2d(std::string& path, std::vector<float>& vec_pts)
{
	std::ofstream file(path.c_str());

	int num = vec_pts.size() / 2;
	file << "#pt2d " << num << std::endl;

	for (int i = 0; i < num; i++) {
		file << vec_pts[i * 2] << " " << vec_pts[i * 2 + 1] << std::endl;
	}

	return 0;
}

int kb::save_pt2d(std::string& path, std::vector<double>& vec_pts)
{
	std::ofstream file(path.c_str());

	int num = vec_pts.size() / 2;
	file << "#pt2d " << num << std::endl;

	for (int i = 0; i < num; i++) {
		file << vec_pts[i * 2] << " " << vec_pts[i * 2 + 1] << std::endl;
	}

	return 0;
}

int kb::load_pt2d(std::string& path, std::vector<float>& vec_pts)
{
	std::ifstream file(path.c_str());

	std::string str1;
	file >> str1;
	int num = 0;
	file >> num;

	for (int i = 0; i < num; i++) {
		float x = 0; file >> x;
		float y = 0; file >> y;

		vec_pts.push_back(x);
		vec_pts.push_back(y);
	}

	return 0;
}

int kb::load_pt2d(std::string& path, std::vector<double>& vec_pts)
{
	std::ifstream file(path.c_str());

	std::string str1;
	file >> str1;
	int num = 0;
	file >> num;

	for (int i = 0; i < num; i++) {
		double x = 0; file >> x;
		double y = 0; file >> y;

		vec_pts.push_back(x);
		vec_pts.push_back(y);
	}

	return 0;
}

int kb::load_pt1d(std::string& path, std::vector<double>& vec_pts)
{
	std::ifstream file(path.c_str());

	std::string str1;
	file >> str1;
	int num = 0;
	file >> num;

	for (int i = 0; i < num; i++) {
		double x = 0; file >> x;

		vec_pts.push_back(x);
	}

	return 0;
}

int kb::save_pt1d(std::string& path, std::vector<double>& vec_pts, int precision)
{
	std::ofstream file(path.c_str());

	if (precision > 5) {
		file.precision(precision);
	}

	int num = vec_pts.size();
	file << "#pt1d " << num << std::endl;

	for (int i = 0; i < num; i++) {
		file << vec_pts[i] << std::endl;
	}

	return 0;
}

int kb::save_pt3d(std::string& path, std::vector<float>& vec_pts)
{
	std::ofstream file(path.c_str());

	int num = vec_pts.size() / 3;
	file << "#pt3d " << num << std::endl;

	for (int i = 0; i < num; i++) {
		file << vec_pts[i * 3] << " " << vec_pts[i * 3 + 1] << " " << vec_pts[i * 3 + 2] << std::endl;
	}

	return 0;
}

int kb::save_pt3d(std::string& path, std::vector<double>& vec_pts)
{
	std::ofstream file(path.c_str());

	int num = vec_pts.size() / 3;
	file << "#pt3d " << num << std::endl;

	for (int i = 0; i < num; i++) {
		file << vec_pts[i * 3] << " " << vec_pts[i * 3 + 1] << " " << vec_pts[i * 3 + 2] << std::endl;
	}

	return 0;
}

//	Nd points
int kb::save_ptNd(std::string& path, std::vector<double>& vec_pts, int dim)
{
	if (dim <= 0)
		return-1;

	int num = vec_pts.size() / dim;

	std::ofstream file(path.c_str());

	file << "#ptNd " << num << " " << dim << std::endl;

	for (int i = 0; i < num; i++) {
		for (int ii = 0; ii < dim; ii++) {
			file << vec_pts[i * dim + ii] << " ";
		}

		file << std::endl;
	}


	return 0;
}

int kb::load_ptNd(std::string& path, std::vector<double>& vec_pts)
{
	std::ifstream file(path.c_str());

	std::string str1;
	file >> str1;
	int num = 0;	file >> num;
	int dim = 0;	file >> dim;

	vec_pts.resize(num * dim);

	for (int i = 0; i < num; i++) {
		for (int ii = 0; ii < dim; ii++) {
			double x = 0;
			file >> x;

			vec_pts[ii + i * dim] = x;
		}
	}

	return 0;
}

int kb::load_pt3d(std::string& path, std::vector<float>& vec_pts)
{
	std::ifstream file(path.c_str());

	std::string str1;
	file >> str1;
	int num = 0;
	file >> num;

	for (int i = 0; i < num; i++) {
		float x = 0; file >> x;
		float y = 0; file >> y;
		float z = 0; file >> z;

		vec_pts.push_back(x);
		vec_pts.push_back(y);
		vec_pts.push_back(z);
	}

	return 0;
}

int kb::load_pt3d(std::string& path, std::vector<double>& vec_pts)
{
	std::ifstream file(path.c_str());

	std::string str1;
	file >> str1;
	int num = 0;
	file >> num;

	for (int i = 0; i < num; i++) {
		double x = 0; file >> x;
		double y = 0; file >> y;
		double z = 0; file >> z;

		vec_pts.push_back(x);
		vec_pts.push_back(y);
		vec_pts.push_back(z);
	}

	return 0;
}
