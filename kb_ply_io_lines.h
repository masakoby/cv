#include <vector>
#include <string>


#pragma once

namespace kb
{
	int save_edge_as_ply_v5(
		std::string& path,
		std::vector<float>& vec_pos,
		std::vector<int>& e2n,
		std::vector<std::vector<int>>& seq_vertex
	);
	int load_edge_as_ply_v5(
		std::string& path,
		std::vector<double>& vec_pos,
		std::vector<int>& vec_edge_idx,
		std::vector<int>& vec_edge_label,
		std::vector<std::vector<int>>& seq_vertex,
		std::vector<int>& seq_label
	);
	int save_edge_as_ply_v6(
		std::string& path,
		std::vector<double>& vec_pos,
		std::vector<int>& vec_vertex_label,
		std::vector<double>& vec_ratio,
		std::vector<int>& vec_edge_idx,
		std::vector<int>& vec_edge_label,
		std::vector<std::vector<int>>& seq_vertex,
		std::vector<int>& seq_label
	);
	int load_edge_as_ply_v6(
		std::string& path,
		std::vector<double>& vec_pos,
		std::vector<double>& vec_ratio,
		std::vector<int>& vec_edge_idx,
		std::vector<int>& vec_edge_label,
		std::vector<std::vector<int>>& seq_vertex,
		std::vector<int>& seq_label
	);

	int save_edge_as_ply_v7(
		std::string& path,
		std::vector<float>& vec_pos,
		std::vector<int>& vec_vertex_label,
		std::vector<float>& vec_radius,
		std::vector<double>& vec_ratio,
		std::vector<int>& vec_edge_idx,
		std::vector<int>& vec_edge_label,
		std::vector<std::vector<int>>& seq_vertex,
		std::vector<int>& seq_label
	);



	int save_line_as_ply(
		std::string& path,
		std::vector<float>& v_pt
		);
	int save_edge_as_ply(
		std::string& path,
		std::vector<double>& vec_pos,
		std::vector<int>& e2n
	);

};