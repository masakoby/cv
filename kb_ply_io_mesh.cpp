#include "kb_ply_io_mesh.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include "kb_mat.h"

int kb::save_mesh_as_ply(
	std::string& path,
	std::vector<double>& vec_pos,
	std::vector<int>& vec_idx)
{
	std::ofstream f(path);

	if (f.is_open() == false)
		return -1;

	int num_vertex = vec_pos.size() / 3;
	int num_element = vec_idx.size() / 3;

	f << "ply" << std::endl;
	f << "format ascii 1.0" << std::endl;
	f << "comment written by koba@oshima.lab" << std::endl;
	f << "element vertex " << num_vertex << std::endl;
	f << "property float x" << std::endl;
	f << "property float y" << std::endl;
	f << "property float z" << std::endl;
	f << "element face " << num_element << std::endl;
	f << "property list uchar int vertex_indices" << std::endl;
	f << "end_header" << std::endl;

	for (int k = 0; k < num_vertex; k++) {
		f << vec_pos[k * 3] << " " << vec_pos[k * 3 + 1] << " " << vec_pos[k * 3 + 2] << " " << std::endl;
	}
	for (int k = 0; k < num_element; k++) {
		f << "3 " << vec_idx[k * 3] << " " << vec_idx[k * 3 + 1] << " " << vec_idx[k * 3 + 2] << " " << std::endl;
	}
	return 0;
}

int kb::save_mesh_as_ply(
	std::string& path,
	std::vector<float>& vec_pos,
	std::vector<int>& vec_idx)
{
	std::ofstream f(path);

	if (f.is_open() == false)
		return -1;

	int num_vertex = vec_pos.size() / 3;
	int num_element = vec_idx.size() / 3;

	f << "ply" << std::endl;
	f << "format ascii 1.0" << std::endl;
	f << "comment kb" << std::endl;
	f << "element vertex " << num_vertex << std::endl;
	f << "property float x" << std::endl;
	f << "property float y" << std::endl;
	f << "property float z" << std::endl;
	f << "element face " << num_element << std::endl;
	f << "property list uchar int vertex_indices" << std::endl;
	f << "end_header" << std::endl;

	for (int k = 0; k < num_vertex; k++) {
		f << vec_pos[k * 3] << " " << vec_pos[k * 3 + 1] << " " << vec_pos[k * 3 + 2] << " " << std::endl;
	}
	for (int k = 0; k < num_element; k++) {
		f << "3 " << vec_idx[k * 3] << " " << vec_idx[k * 3 + 1] << " " << vec_idx[k * 3 + 2] << " " << std::endl;
	}
	return 0;
}

int kb::load_mesh_as_ply(
	std::string& path,
	std::vector<double>& vec_pos,
	std::vector<double>& vec_nv,
	std::vector<int>& vec_idx)
{
	std::ifstream f(path);

	if (f.is_open() == false)
		return -1;

	char buf[1024];
	int num_vertex = -1;// vec_pos.size() / 3;
	int num_element = -1;// vec_idx.size() / 3;

	int num_max_header = 1000;
	//	load header 
	int cnt = 0;
	int cnt_prop_v = 0;
	int cnt_prop_e = 0;
	int flag_vertex = 0;
	int flag_element = 0;
	while (1) {
		f.getline(buf, 1024);
		std::string str1 = buf;

		if (str1.find("end_header") != std::string::npos)
			break;



		if (str1.find("property") != std::string::npos) {
			if (flag_vertex == 1) {
				cnt_prop_v++;
			}
			else if (flag_element == 1) {
				cnt_prop_e++;
			}
		}

		if (str1.find("element vertex ") != std::string::npos) {
			std::stringstream ss(str1);

			std::string str2;
			ss >> str2;
			ss >> str2;
			ss >> str2;

			num_vertex = atoi(str2.c_str());
			flag_vertex = 1;
			flag_element = 0;
		}

		if (str1.find("element face ") != std::string::npos) {
			std::stringstream ss(str1);

			std::string str2;
			ss >> str2;
			ss >> str2;
			ss >> str2;

			num_element = atoi(str2.c_str());

			flag_vertex = 0;
			flag_element = 1;
		}


		cnt++;
		if (num_max_header < cnt)
			return -1;

	}

	if (num_vertex < 0 || num_element < 0)
		return -1;

	vec_pos.resize(num_vertex * 3);
	vec_nv.resize(num_element * 3);
	vec_idx.resize(num_element * 3);
	//vec_num.resize(num_element);

	std::string str1;
	for (int k = 0; k < num_vertex; k++) {
		f >> str1;
		vec_pos[k * 3] = atof(str1.c_str());
		f >> str1;
		vec_pos[k * 3 + 1] = atof(str1.c_str());
		f >> str1;
		vec_pos[k * 3 + 2] = atof(str1.c_str());

		for (int i = 3; i < cnt_prop_v; i++) {
			f >> str1;
		}
	}

	for (int k = 0; k < num_element; k++) {
		f >> str1;
		//vec_num[k] = atoi(str1.c_str());

		f >> str1;
		vec_idx[k * 3] = atoi(str1.c_str());
		f >> str1;
		vec_idx[k * 3 + 1] = atoi(str1.c_str());
		f >> str1;
		vec_idx[k * 3 + 2] = atoi(str1.c_str());

		for (int i = 3; i < cnt_prop_e; i++) {
			f >> str1;
		}
	}

	//	calculate normal vector
	int error = 0;
	for (int k = 0; k < num_element; k++) {
		//check vertex and element index consistency
		int flags = 0;
		for (int i = 0; i < 3; i++) {
			int ii = vec_idx[k * 3 + i];
			if (ii < 0 || num_vertex <= ii) {
				error++;
				flags++;
			}
		}
		if (flags > 0)
			continue;

		double p[3][3];
		for (int i = 0; i < 3; i++) {
			int ii = vec_idx[k * 3 + i];

			p[i][0] = vec_pos[ii * 3];
			p[i][1] = vec_pos[ii * 3 + 1];
			p[i][2] = vec_pos[ii * 3 + 2];
		}

		double v1[3] = { p[1][0] - p[0][0], p[1][1] - p[0][1], p[1][2] - p[0][2] };
		double v2[3] = { p[2][0] - p[0][0], p[2][1] - p[0][1], p[2][2] - p[0][2] };
		double v12[3];
		kb::crossproduct(v1, v2, v12);

		vec_nv[k * 3] = v12[0];
		vec_nv[k * 3 + 1] = v12[1];
		vec_nv[k * 3 + 2] = v12[2];

	}
	if (error > 0) {
		std::cout << "error: inconsistency of vertex and element indices: " << error << std::endl;
	}

	return 0;
}

int kb::load_mesh_as_ply(
	std::string& path,
	std::vector<float>& vec_pos,
	std::vector<float>& vec_nv,
	std::vector<int>& vec_idx)
{
	std::ifstream f(path);

	if (f.is_open() == false)
		return -1;

	char buf[1024];
	int num_vertex = -1;// vec_pos.size() / 3;
	int num_element = -1;// vec_idx.size() / 3;

	int num_max_header = 1000;
	//	load header 
	int cnt = 0;
	int cnt_prop_v = 0;
	int cnt_prop_e = 0;
	int flag_vertex = 0;
	int flag_element = 0;
	while (1) {
		f.getline(buf, 1024);
		std::string str1 = buf;

		if (str1.find("end_header") != std::string::npos)
			break;



		if (str1.find("property") != std::string::npos) {
			if (flag_vertex == 1) {
				cnt_prop_v++;
			}
			else if (flag_element == 1) {
				cnt_prop_e++;
			}
		}

		if (str1.find("element vertex ") != std::string::npos) {
			std::stringstream ss(str1);

			std::string str2;
			ss >> str2;
			ss >> str2;
			ss >> str2;

			num_vertex = atoi(str2.c_str());
			flag_vertex = 1;
			flag_element = 0;
		}

		if (str1.find("element face ") != std::string::npos) {
			std::stringstream ss(str1);

			std::string str2;
			ss >> str2;
			ss >> str2;
			ss >> str2;

			num_element = atoi(str2.c_str());

			flag_vertex = 0;
			flag_element = 1;
		}


		cnt++;
		if (num_max_header < cnt)
			return -1;

	}

	if (num_vertex < 0 || num_element < 0)
		return -1;

	vec_pos.resize(num_vertex * 3);
	vec_nv.resize(num_element * 3);
	vec_idx.resize(num_element * 3);
	//vec_num.resize(num_element);

	std::string str1;
	for (int k = 0; k < num_vertex; k++) {
		f >> str1;
		vec_pos[k * 3] = atof(str1.c_str());
		f >> str1;
		vec_pos[k * 3 + 1] = atof(str1.c_str());
		f >> str1;
		vec_pos[k * 3 + 2] = atof(str1.c_str());

		for (int i = 3; i < cnt_prop_v; i++) {
			f >> str1;
		}
	}

	for (int k = 0; k < num_element; k++) {
		f >> str1;
		//vec_num[k] = atoi(str1.c_str());
		int num = atoi(str1.c_str());

		f >> str1;
		vec_idx[k * 3] = atoi(str1.c_str());
		f >> str1;
		vec_idx[k * 3 + 1] = atoi(str1.c_str());
		f >> str1;
		vec_idx[k * 3 + 2] = atoi(str1.c_str());

		for (int i = 4; i < cnt_prop_e; i++) {
			f >> str1;
		}
	}

	//	calculate normal vector
	int error = 0;
	for (int k = 0; k < num_element; k++) {
		//check vertex and element index consistency
		int flags = 0;
		for (int i = 0; i < 3; i++) {
			int ii = vec_idx[k * 3 + i];
			if (ii < 0 || num_vertex <= ii) {
				error++;
				flags++;
			}
		}
		if (flags > 0)
			continue;

		double p[3][3];
		for (int i = 0; i < 3; i++) {
			int ii = vec_idx[k * 3 + i];

			p[i][0] = vec_pos[ii * 3];
			p[i][1] = vec_pos[ii * 3 + 1];
			p[i][2] = vec_pos[ii * 3 + 2];
		}

		double v1[3] = { p[1][0] - p[0][0], p[1][1] - p[0][1], p[1][2] - p[0][2] };
		double v2[3] = { p[2][0] - p[0][0], p[2][1] - p[0][1], p[2][2] - p[0][2] };
		double v12[3];
		kb::crossproduct(v1, v2, v12);

		vec_nv[k * 3] = v12[0];
		vec_nv[k * 3 + 1] = v12[1];
		vec_nv[k * 3 + 2] = v12[2];

	}
	if (error > 0) {
		std::cout << "error: inconsistency of vertex and element indices: " << error << std::endl;
	}

	return 0;
}

int kb::save_mesh_as_ply_bin(
	std::string& path,
	std::vector<float>& vec_pos,
	std::vector<int>& vec_idx)
{
	std::ofstream f(path);

	if (f.is_open() == false)
		return -1;

	int num_vertex = vec_pos.size() / 3;
	int num_element = vec_idx.size() / 3;

	f << "ply" << std::endl;
	f << "format binary_little_endian 1.0" << std::endl;
	//f << "comment written by koba@chi.co.jp" << std::endl;
	f << "element vertex " << num_vertex << std::endl;
	f << "property float x" << std::endl;
	f << "property float y" << std::endl;
	f << "property float z" << std::endl;
	f << "element face " << num_element << std::endl;
	f << "property list uchar int vertex_indices" << std::endl;
	f << "end_header" << std::endl;

	float* ptr1 = &(vec_pos[0]);
	f.write((char*)ptr1, sizeof(float) * num_vertex * 3);

	//for (int k = 0; k < num_vertex; k++) {
	//	f << vec_pos[k * 3] << " " << vec_pos[k * 3 + 1] << " " << vec_pos[k * 3 + 2] << " " << std::endl;
	//}

	//std::vector<int> vec_idx2;
	//vec_idx2.resize(num_element*4);
	for (int k = 0; k < num_element; k++) {
		unsigned char a = 3;
		int b[3] = { vec_idx[k * 3 + 0], vec_idx[k * 3 + 1], vec_idx[k * 3 + 2] };

		f.write((char*)&a, 1);
		f.write((char*)b, sizeof(int) * 3);

		//vec_idx2[k * 4 + 0] = 3;
		//vec_idx2[k * 4 + 1] = vec_idx[k * 3 + 0];
		//vec_idx2[k * 4 + 2] = vec_idx[k * 3 + 1];
		//vec_idx2[k * 4 + 3] = vec_idx[k * 3 + 2];
	}
	//int* ptr2 = &(vec_idx2[0]);
	//f.write((char*)ptr2, sizeof(int) * num_element * 4);


	return 0;
}


