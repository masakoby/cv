#include <fstream>
#include <iostream>

#include "kb_cv_io.h"
#include "kb_csv.h"

//-----------------------------------------------------------------------------------------------

int kb::save_pt2d(std::string& path, std::vector<cv::Point2f>& vec_pts)
{
	std::ofstream file(path.c_str());

	int num=vec_pts.size();
	file<<"#pt2d "<<num<<std::endl;

	for(int i=0;i<num;i++){
		file<<vec_pts[i].x<<" "<<vec_pts[i].y<<std::endl;
	}

	return 0;
}


int kb::save_pt2d_csv(std::string& path, std::vector<double>& vec_pts)
{
	std::ofstream file(path.c_str());

	int num=vec_pts.size()/2;

	for(int i=0;i<num;i++){
		file<<vec_pts[i*2]<<","<<vec_pts[i*2+1]<<std::endl;
	}

	return 0;
}
int kb::save_ptNd_csv(std::string& path, std::vector<double>& vec_pts, int dim)
{
	if( dim<1 ){
		dim=1;
	}

	std::ofstream file(path.c_str());

	int num=vec_pts.size()/dim;

	for(int i=0;i<num;i++){
		file<<vec_pts[i*dim];
		for(int ii=1;ii<dim;ii++){
			file<<","<<vec_pts[i*dim+ii];
		}
		file<<std::endl;
	}

	return 0;
}


int kb::load_pt2d(std::string& path, std::vector<cv::Point2f>& vec_pts)
{
	std::ifstream file(path.c_str());

	std::string str1;
	file>>str1;
	int num=0;
	file>>num;

	for(int i=0;i<num;i++){
		float x=0; file>>x;
		float y=0; file>>y;

		vec_pts.push_back( cv::Point2f(x, y) );
	}

	return 0;
}


//-----------------------------------------------------------------------------------------------
int kb::save_pt3d(std::string& path, std::vector<cv::Point3f>& vec_pts)
{
	std::ofstream file(path.c_str());

	int num=vec_pts.size();
	file<<"#pt3d "<<num<<std::endl;

	for(int i=0;i<num;i++){
		file<<vec_pts[i].x<<" "<<vec_pts[i].y<<" "<<vec_pts[i].z<<std::endl;
	}

	return 0;
}


int kb::load_pt3d(std::string& path, std::vector<cv::Point3f>& vec_pts)
{
	std::ifstream file(path.c_str());

	std::string str1;
	file>>str1;
	int num=0;
	file>>num;

	for(int i=0;i<num;i++){
		float x=0; file>>x;
		float y=0; file>>y;
		float z=0; file>>z;

		vec_pts.push_back( cv::Point3f(x, y, z) );
	}

	return 0;
}



//-----------------------------------------------------------------------------------------------
//	2d line 
int kb::save_line2d(std::string& path, std::vector<double>& line_points)
{
	std::ofstream file( path.c_str() );

	int num_lines = line_points.size()/4;
	file<<"line2d "<<num_lines<<std::endl;
	for(int i=0;i<num_lines;i++){
		file<<line_points[i*4]<<" "<<line_points[i*4+1]<<" "<<line_points[i*4+2]<<" "<<line_points[i*4+3]<<std::endl;
	}

	return 0;
}

int kb::load_line2d(std::string& path, std::vector<double>& line_points)
{
	std::ifstream file( path.c_str() );
	std::string buf;
	file>>buf;
	int num_lines; file>>num_lines;
	std::cout<<buf<<" "<<num_lines<<std::endl;

	for(int k=0;k<num_lines;k++){
		double x1, y1, x2, y2;
		file>>x1;
		file>>y1;
		file>>x2;
		file>>y2;
		line_points.push_back(x1);
		line_points.push_back(y1);
		line_points.push_back(x2);
		line_points.push_back(y2);
	}

	return 0;
}

int kb::load_line2d(std::string& path, std::vector<cv::Point2f>& vec_obj)
{
	std::vector<std::vector<std::string>> vv;
	if (kb::load_space(path, vv) < 0)
		return -1;

	size_t nn = vv.size();
	std::cout << nn << std::endl;
	for (size_t kk = 0; kk < nn; kk++) {
		cv::Point2f p1, p2;

		size_t n = vv[kk].size();
		if (n < 4)
			continue;

		std::string::size_type idx = vv[kk][0].find("#");
		if (idx != std::string::npos) {
			std::cout << vv[kk][1] << std::endl;
			continue;
		}
		p1.x = atof(vv[kk][0].c_str());
		p1.y = atof(vv[kk][1].c_str());
		p2.x = atof(vv[kk][2].c_str());
		p2.y = atof(vv[kk][3].c_str());

		vec_obj.push_back(p1);
		vec_obj.push_back(p2);
	}

	return 0;
}


//-----------------------------------------------------------------------------------------------
//	3d line 
int kb::save_line3d(std::string& path, std::vector<double>& line_points)
{
	std::ofstream file( path.c_str() );

	int num_lines = line_points.size()/6;
	file<<"line3d "<<num_lines<<std::endl;
	for(int i=0;i<num_lines;i++){
		file<<line_points[i*6]<<" "<<line_points[i*6+1]<<" "<<line_points[i*6+2]<<" "<<
			line_points[i*6+3]<<" "<<line_points[i*6+4]<<" "<<line_points[i*6+5]<<std::endl;
	}

	return 0;
}

int kb::load_line3d(std::string& path1, std::vector<double>& line_points)
{
	std::ifstream file( path1.c_str() );
	std::string buf;
	file>>buf;
	int num_lines; file>>num_lines;
	std::cout<<buf<<" "<<num_lines<<std::endl;

	for(int k=0;k<num_lines;k++){
		double x1, y1, z1, x2, y2, z2;
		file>>x1;
		file>>y1;
		file>>z1;
		file>>x2;
		file>>y2;
		file>>z2;
		line_points.push_back(x1);
		line_points.push_back(y1);
		line_points.push_back(z1);
		line_points.push_back(x2);
		line_points.push_back(y2);
		line_points.push_back(z2);
	}

	return 0;
}

//-----------------------------------------------------------------------------------------------

int kb::save_vec_index(std::string& path, std::vector<int>& vec_index)
{
	std::ofstream file( path.c_str() );

	int num = vec_index.size();
	file<<"index1d "<<num<<std::endl;
	for(int i=0;i<num;i++){
		file<<vec_index[i*6]<<std::endl;
	}

	return 0;
}

int kb::load_vec_index(std::string& path1, std::vector<int>& vec_index)
{
	std::ifstream file( path1.c_str() );
	std::string buf;
	file>>buf;
	int num=0; file>>num;
	//std::cout<<buf<<" "<<num<<std::endl;

	for(int k=0;k<num;k++){
		int idx=0;
		file>>idx;
		vec_index.push_back(idx);
	}

	return 0;
}

int kb::save_pt3d_as_ply(std::string& path, std::vector<cv::Point3d>& pts)
{
	std::ofstream file(path.c_str());
	if (file.is_open() == false)
		return -1;

	file.precision(10);


	int num = pts.size();
	file << "ply" << std::endl;
	file << "format ascii 1.0" << std::endl;
	file << "element vertex " << num << std::endl;
	file << "property float x" << std::endl;
	file << "property float y" << std::endl;
	file << "property float z" << std::endl;
	file << "end_header" << std::endl;

	for (int ii = 0; ii < num; ii++) {
		file << pts[ii].x << " " << pts[ii].y << " " << pts[ii].z << std::endl;
	}

	return 0;
}

int kb::save_pt3d_as_ply(std::string& path, std::vector<cv::Point3f>& pts)
{
	std::ofstream file(path.c_str());
	if (file.is_open() == false)
		return -1;

	file.precision(10);


	int num = pts.size();
	file << "ply" << std::endl;
	file << "format ascii 1.0" << std::endl;
	file << "element vertex " << num << std::endl;
	file << "property float x" << std::endl;
	file << "property float y" << std::endl;
	file << "property float z" << std::endl;
	file << "end_header" << std::endl;

	for (int ii = 0; ii < num; ii++) {
		file << pts[ii].x << " " << pts[ii].y << " " << pts[ii].z << std::endl;
	}

	return 0;
}

