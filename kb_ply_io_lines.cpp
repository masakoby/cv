#include "kb_ply_io_lines.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include "kb_csv.h"

int kb::save_edge_as_ply_v5(
	std::string& path,
	std::vector<float>& vec_pos,
	std::vector<int>& e2n,
	std::vector<std::vector<int>>& ls2n
)
{
	int cntn = vec_pos.size()/3;
	int cnte = e2n.size()/2;
	int cntSeg = ls2n.size();

	std::ofstream f(path);

	if (f.is_open() == false)
		return -1;



	f << "ply" << std::endl;
	f << "format ascii 1.0" << std::endl;
	f << "element vertex " << cntn << std::endl;
	f << "property float x" << std::endl;
	f << "property float y" << std::endl;
	f << "property float z" << std::endl;
	f << "property int label" << std::endl;
	f << "property int attribute" << std::endl;
	f << "property float radius" << std::endl;
	f << "element edge " << cnte << std::endl;
	f << "property int vertex1" << std::endl;
	f << "property int vertex2" << std::endl;
	f << "property int label" << std::endl;
	if (cntSeg > 0) {
		f << "element vertex_seq " << cntSeg << std::endl;
		f << "property int label" << std::endl;
		f << "property list int int vertex_indices" << std::endl;
	}
	f << "end_header" << std::endl;

	for (int k = 0; k < cntn; k++) {
		int k_3 = k * 3;
		f << vec_pos[k_3 + 0] << " "
			<< vec_pos[k_3 + 1] << " "
			<< vec_pos[k_3 + 2] << " "
			<< "0 0 0 "
			<< std::endl;
	}
	for (int k = 0; k < cnte; k++) {
		f << e2n[k * 2] << " " << e2n[k * 2 + 1] <<" 0"<< std::endl;
	}

	if (cntSeg > 0) {
		for (int k = 0; k < cntSeg; k++) {
			int cntS = ls2n[k].size();
			int label = 0;
			f << label << " " << cntS << " ";
			for (int i = 0; i < cntS; i++) {
				f << ls2n[k][i] << " ";
			}
			f << std::endl;
		}
	}

	return 0;
}

int kb::save_edge_as_ply_v6(
	std::string& path,
	std::vector<double>& vec_pos,
	std::vector<int>& vec_vertex_label,
	std::vector<double>& vec_ratio,
	std::vector<int>& vec_edge_idx,
	std::vector<int>& vec_edge_label,
	std::vector<std::vector<int>>& seq_vertex,
	std::vector<int>& seq_label
)
{
	int cntn = vec_pos.size() / 3;
	int cntn2 = vec_vertex_label.size();
	int cntn3 = vec_ratio.size();
	int cnte = vec_edge_idx.size() / 2;
	int cnte2 = vec_edge_label.size();
	int cntSeg = seq_vertex.size();
	int cntSeg2 = seq_label.size();

	if (cntn != cntn2 || cntn != cntn3)
		return -1;
	if (cnte != cnte2)
		return -1;
	if (cntSeg != cntSeg2)
		return -1;

	std::ofstream f(path);

	if (f.is_open() == false)
		return -1;



	f << "ply" << std::endl;
	f << "format ascii 1.0" << std::endl;
	f << "element vertex " << cntn << std::endl;
	f << "property float x" << std::endl;
	f << "property float y" << std::endl;
	f << "property float z" << std::endl;
	f << "property int label" << std::endl;
	f << "property int attribute" << std::endl;
	f << "property float radius" << std::endl;
	f << "property float ratio" << std::endl;
	f << "element edge " << cnte << std::endl;
	f << "property int vertex1" << std::endl;
	f << "property int vertex2" << std::endl;
	f << "property int label" << std::endl;
	if (cntSeg > 0) {
		f << "element vertex_seq " << cntSeg << std::endl;
		f << "property int label" << std::endl;
		f << "property list int int vertex_indices" << std::endl;
	}
	f << "end_header" << std::endl;

	for (int k = 0; k < cntn; k++) {
		int k_3 = k * 3;
		f << vec_pos[k_3 + 0] << " "
			<< vec_pos[k_3 + 1] << " "
			<< vec_pos[k_3 + 2] << " "
			<< vec_vertex_label[k]<<" 0 0 "<< vec_ratio[k]<<" "
			<< std::endl;
	}
	for (int k = 0; k < cnte; k++) {
		f << vec_edge_idx[k * 2] << " " << vec_edge_idx[k * 2 + 1] << " "<< vec_edge_label[k] << std::endl;
	}

	if (cntSeg > 0) {
		for (int k = 0; k < cntSeg; k++) {
			int cntS = seq_vertex[k].size();
			int label = seq_label[k];
			f << label << " " << cntS << " ";
			for (int i = 0; i < cntS; i++) {
				f << seq_vertex[k][i] << " ";
			}
			f << std::endl;
		}
	}

	return 0;
}

int kb::save_edge_as_ply_v7(
	std::string& path,
	std::vector<float>& vec_pos,
	std::vector<int>& vec_vertex_label,
	std::vector<float>& vec_radius,
	std::vector<double>& vec_ratio,
	std::vector<int>& vec_edge_idx,
	std::vector<int>& vec_edge_label,
	std::vector<std::vector<int>>& seq_vertex,
	std::vector<int>& seq_label
)
{
	int cntn = vec_pos.size() / 3;
	int cntn2 = vec_vertex_label.size();
	int cntn3 = vec_radius.size();
	int cntn4 = vec_ratio.size();
	int cnte = vec_edge_idx.size() / 2;
	int cnte2 = vec_edge_label.size();
	int cntSeg = seq_vertex.size();
	int cntSeg2 = seq_label.size();

	if (cntn != cntn2 || cntn != cntn3 || cntn != cntn4)
		return -1;
	if (cnte != cnte2)
		return -1;
	if (cntSeg != cntSeg2)
		return -1;

	std::ofstream f(path);

	if (f.is_open() == false)
		return -1;



	f << "ply" << std::endl;
	f << "format ascii 1.0" << std::endl;
	f << "element vertex " << cntn << std::endl;
	f << "property float x" << std::endl;
	f << "property float y" << std::endl;
	f << "property float z" << std::endl;
	f << "property int label" << std::endl;
	f << "property int attribute" << std::endl;
	f << "property float radius" << std::endl;
	f << "property float ratio" << std::endl;
	f << "element edge " << cnte << std::endl;
	f << "property int vertex1" << std::endl;
	f << "property int vertex2" << std::endl;
	f << "property int label" << std::endl;
	if (cntSeg > 0) {
		f << "element vertex_seq " << cntSeg << std::endl;
		f << "property int label" << std::endl;
		f << "property list int int vertex_indices" << std::endl;
	}
	f << "end_header" << std::endl;

	for (int k = 0; k < cntn; k++) {
		int k_3 = k * 3;
		f << vec_pos[k_3 + 0] << " "
			<< vec_pos[k_3 + 1] << " "
			<< vec_pos[k_3 + 2] << " "
			<< vec_vertex_label[k] << " 0 "<<vec_radius[k]<<" " << vec_ratio[k] << " "
			<< std::endl;
	}
	for (int k = 0; k < cnte; k++) {
		f << vec_edge_idx[k * 2] << " " << vec_edge_idx[k * 2 + 1] << " " << vec_edge_label[k] << std::endl;
	}

	if (cntSeg > 0) {
		for (int k = 0; k < cntSeg; k++) {
			int cntS = seq_vertex[k].size();
			int label = seq_label[k];
			f << label << " " << cntS << " ";
			for (int i = 0; i < cntS; i++) {
				f << seq_vertex[k][i] << " ";
			}
			f << std::endl;
		}
	}

	return 0;
}


int kb::load_edge_as_ply_v6(
	std::string& path,
	std::vector<double>& vec_pos,
	std::vector<double>& vec_ratio,
	std::vector<int>& vec_edge_idx,
	std::vector<int>& vec_edge_label,
	std::vector<std::vector<int>>& seq_vertex,
	std::vector<int>& seq_label
)
{
	std::vector<std::vector<std::string>> vv;
	if (kb::load_csv(path, vv, ' ') < 0)
		return -1;

	int num_vv = vv.size();

	int num_vertex = -1;// vec_pos.size() / 3;
	int num_edge = -1;// vec_idx.size() / 3;
	int num_seq = -1;
	int start = 0;

	//	load header 
	for (int k = 0; k < num_vv; k++) {
		int num_word = vv[k].size();
		if (num_word == 0) {
			continue;
		}
		//	header end
		if (vv[k][0].find("end_header") != std::string::npos) {
			start = k + 1;
			break;
		}

		if (num_word < 3) {
			continue;
		}
		std::cout << vv[k][0] << " " << vv[k][1] << " " << vv[k][2] << std::endl;

		if (vv[k][0] == "element" && vv[k][1] == "vertex") {
			num_vertex = std::stoi(vv[k][2]);
		}
		else if (vv[k][0] == "element" && vv[k][1] == "edge") {
			num_edge = std::stoi(vv[k][2]);
		}
		else if (vv[k][0] == "element" && vv[k][1] == "vertex_seq") {
			num_seq = std::stoi(vv[k][2]);
		}
	}


	std::cout << "number of vertices=" << num_vertex << std::endl;
	std::cout << "number of edges=" << num_edge << std::endl;
	std::cout << "number of lines=" << num_seq << std::endl;
	if (num_vertex < 0 || num_edge < 0)
		return -1;

	vec_pos.resize(num_vertex * 3);
	vec_ratio.resize(num_vertex, -1);
	vec_edge_idx.resize(num_edge * 2);
	vec_edge_label.resize(num_edge);
	seq_vertex.resize(num_seq);
	seq_label.resize(num_seq);

	for (int k = 0; k < num_vertex; k++) {
		vec_pos[k * 3 + 0] = std::stod(vv[k + start][0]);
		vec_pos[k * 3 + 1] = std::stod(vv[k + start][1]);
		vec_pos[k * 3 + 2] = std::stod(vv[k + start][2]);
		int num_word=vv[k + start].size();
		if (num_word >= 7) {
			vec_ratio[k] = std::stod(vv[k + start][6]);
		}
	}
	start = start + num_vertex;

	for (int k = 0; k < num_edge; k++) {
		vec_edge_idx[k * 2 + 0] = std::stoi(vv[k + start][0]);
		vec_edge_idx[k * 2 + 1] = std::stoi(vv[k + start][1]);
		vec_edge_label[k] = std::stoi(vv[k + start][2]);
	}
	start = start + num_edge;

	for (int k = 0; k < num_seq; k++) {
		seq_label[k] = std::stoi(vv[k + start][0]);
		int num1 = std::stoi(vv[k + start][1]);

		std::vector<int> vv1;
		for (int i = 0; i < num1; i++) {
			vv1.push_back(std::stoi(vv[k + start][i + 2]));
		}
		seq_vertex[k] = vv1;
	}



	return 0;
}


int kb::load_edge_as_ply_v5(
	std::string& path,
	std::vector<double>& vec_pos,
	std::vector<int>& vec_edge_idx,
	std::vector<int>& vec_edge_label,
	std::vector<std::vector<int>>& seq_vertex,
	std::vector<int>& seq_label
)
{
	std::vector<std::vector<std::string>> vv;
	if (kb::load_csv(path, vv, ' ') < 0)
		return -1;

	int num_vv = vv.size();

	int num_vertex = -1;// vec_pos.size() / 3;
	int num_edge = -1;// vec_idx.size() / 3;
	int num_seq = -1;
	int start = 0;

	//	load header 
	for (int k = 0; k < num_vv; k++) {
		int num_word = vv[k].size();
		if (num_word == 0) {
			continue;
		}
		//	header end
		if (vv[k][0].find("end_header") != std::string::npos) {
			start = k + 1;
			break;
		}

		if (num_word<3) {
			continue;
		}
		std::cout << vv[k][0] << " " << vv[k][1] << " " << vv[k][2] << std::endl;

		if (vv[k][0]=="element" && vv[k][1]=="vertex") {
			num_vertex = std::stoi(vv[k][2]);
		}
		else if (vv[k][0] == "element" && vv[k][1] == "edge") {
			num_edge = std::stoi(vv[k][2]);
		}
		else if (vv[k][0] == "element" && vv[k][1] == "vertex_seq") {
			num_seq = std::stoi(vv[k][2]);
		}
	}


	std::cout << "number of vertices=" << num_vertex << std::endl;
	std::cout << "number of edges=" << num_edge << std::endl;
	std::cout << "number of lines=" << num_seq << std::endl;
	if (num_vertex < 0 || num_edge < 0)
		return -1;

	vec_pos.resize(num_vertex * 3);
	vec_edge_idx.resize(num_edge * 2);
	vec_edge_label.resize(num_edge);
	seq_vertex.resize(num_seq);
	seq_label.resize(num_seq);

	for (int k = 0; k < num_vertex; k++) {
		vec_pos[k * 3 + 0] = std::stod(vv[k + start][0]);
		vec_pos[k * 3 + 1] = std::stod(vv[k + start][1]);
		vec_pos[k * 3 + 2] = std::stod(vv[k + start][2]);
	}
	start = start + num_vertex;

	for (int k = 0; k < num_edge; k++) {
		vec_edge_idx[k * 2 + 0] = std::stoi(vv[k + start][0]);
		vec_edge_idx[k * 2 + 1] = std::stoi(vv[k + start][1]);
		vec_edge_label[k] = std::stoi(vv[k + start][2]);
	}
	start = start + num_edge;

	for (int k = 0; k < num_seq; k++) {
		seq_label[k] = std::stoi(vv[k + start][0]);
		int num1 = std::stoi(vv[k + start][1]);

		std::vector<int> vv1;
		for (int i = 0; i < num1; i++) {
			vv1.push_back(std::stoi(vv[k + start][i+2]));
		}
		seq_vertex[k] = vv1;
	}



	return 0;
}

#if 0
int kb::load_edge_as_ply_v5(
	std::string& path,
	std::vector<double>& vec_pos,
	std::vector<int>& vec_edge_idx,
	std::vector<int>& vec_edge_label,
	std::vector<std::vector<int>>& seq_vertex,
	std::vector<int>& seq_label
)
{
	std::ifstream f(path);

	if (f.is_open() == false)
		return -1;

	char buf[1024];
	int num_vertex = -1;// vec_pos.size() / 3;
	int num_edge = -1;// vec_idx.size() / 3;
	int num_seq = -1;
	int flag_vertex = 0;
	int flag_edge = 0;
	int step_vertex = 0;
	int step_edge = 0;


	//	ヘッダー最大行数を仮に以下とする
	int num_max_header = 1000;

	//	load header 
	int cnt = 0;
	while (1) {
		f.getline(buf, 1024);
		std::string str1 = buf;

		if (str1.find("end_header") != std::string::npos)
			break;


		if (str1.find("element vertex ") != std::string::npos) {
			std::stringstream ss(str1);

			std::string str2;
			ss >> str2;
			ss >> str2;
			ss >> str2;

			num_vertex = atoi(str2.c_str());
			flag_vertex = 1;
			flag_edge = 0;
		}
		else if (str1.find("element edge ") != std::string::npos) {
			std::stringstream ss(str1);

			std::string str2;
			ss >> str2;
			ss >> str2;
			ss >> str2;

			num_edge = atoi(str2.c_str());

			flag_vertex = 0;
			flag_edge = 1;
		}
		else if (str1.find("element edge ") != std::string::npos) {
			std::stringstream ss(str1);

			std::string str2;
			ss >> str2;
			ss >> str2;
			ss >> str2;

			num_edge = atoi(str2.c_str());

			flag_vertex = 0;
			flag_edge = 1;
		}
		else if (str1.find("element vertex_seq ") != std::string::npos) {
			std::stringstream ss(str1);

			std::string str2;
			ss >> str2;
			ss >> str2;
			ss >> str2;

			num_seq = atoi(str2.c_str());

			flag_vertex = 0;
			flag_edge = 0;
		}
		else if (str1.find("property ") != std::string::npos) {
			if (flag_vertex > 0) {
				step_vertex++;
			}
			if (flag_edge > 0) {
				step_edge++;
			}
		}

		cnt++;
		if (num_max_header < cnt)
			return -1;

	}

	std::cout << num_vertex << " " << num_edge << std::endl;
	if (num_vertex < 0 || num_edge < 0)
		return -1;

	vec_pos.resize(num_vertex * 3);
	vec_edge_idx.resize(num_edge * 2);
	vec_edge_label.resize(num_edge * 2);
	seq_vertex.resize(num_seq);
	seq_label.resize(num_seq);

	std::string str1;
	for (int k = 0; k < num_vertex; k++) {
		f >> str1;
		vec_pos[k * 3] = atof(str1.c_str());
		f >> str1;
		vec_pos[k * 3 + 1] = atof(str1.c_str());
		f >> str1;
		vec_pos[k * 3 + 2] = atof(str1.c_str());

		for (int i = 3; i < step_vertex; i++) {
			f >> str1;
		}
	}

	for (int k = 0; k < num_edge; k++) {

		f >> str1;
		vec_edge_idx[k * 2] = atoi(str1.c_str());
		f >> str1;
		vec_edge_idx[k * 2 + 1] = atoi(str1.c_str());
		f >> str1;
		vec_edge_label[k] = atoi(str1.c_str());

		for (int i = 3; i < step_edge; i++) {
			f >> str1;
		}
	}

	for (int k = 0; k < num_seq; k++) {

		f >> str1;
		seq_label[k] = atoi(str1.c_str());

		f >> str1;
		int num1 = atoi(str1.c_str());
		std::vector<int> vv;
		for (int i = 0; i < num1; i++) {
			f >> str1;
			vv.push_back(atoi(str1.c_str()));
		}
		seq_vertex[k] = vv;
	}



	return 0;
}
#endif

int kb::save_line_as_ply(
	std::string& path,
	std::vector<float>& v_pt
)
{
	std::ofstream f(path);

	if (f.is_open() == false)
		return -1;

	int num_vertex = v_pt.size() / 3;

	f << "ply" << std::endl;
	f << "format ascii 1.0" << std::endl;
	f << "comment kb" << std::endl;
	f << "element vertex " << num_vertex << std::endl;
	f << "property float x" << std::endl;
	f << "property float y" << std::endl;
	f << "property float z" << std::endl;
	f << "element edge " << num_vertex-1 << std::endl;
	f << "property int vertex1" << std::endl;
	f << "property int vertex2" << std::endl;
	f << "end_header" << std::endl;

	for (int k = 0; k < num_vertex; k++) {
		f << v_pt[k * 3] << " " << v_pt[k * 3 + 1] << " " << v_pt[k * 3 + 2] << " " << std::endl;
	}
	for (int k = 0; k < num_vertex-1; k++) {
		f <<  k << " " << k+1 << " " << std::endl;
	}

	return 0;
}

int kb::save_edge_as_ply(
	std::string& path,
	std::vector<double>& vec_pos,
	std::vector<int>& e2n
)
{
	int cntn = vec_pos.size() / 3;
	int cnte = e2n.size() / 2;

	std::ofstream f(path);

	if (f.is_open() == false)
		return -1;



	f << "ply" << std::endl;
	f << "format ascii 1.0" << std::endl;
	f << "element vertex " << cntn << std::endl;
	f << "property float x" << std::endl;
	f << "property float y" << std::endl;
	f << "property float z" << std::endl;
	f << "element edge " << cnte << std::endl;
	f << "property int vertex1" << std::endl;
	f << "property int vertex2" << std::endl;
	f << "end_header" << std::endl;

	for (int k = 0; k < cntn; k++) {
		int k_3 = k * 3;
		f << vec_pos[k_3 + 0] << " "
			<< vec_pos[k_3 + 1] << " "
			<< vec_pos[k_3 + 2] << " "
			<< std::endl;
	}
	for (int k = 0; k < cnte; k++) {
		f << e2n[k * 2] << " " << e2n[k * 2 + 1] << std::endl;
	}


	return 0;
}
