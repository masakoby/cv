#include <string>
#include <vector>

#pragma once

namespace kb
{
	//	PLYファイル保存
	int save_mesh_as_ply(
		std::string& path,
		std::vector<float>& vec_pos,
		std::vector<int>& vec_idx);
	int save_mesh_as_ply(
		std::string& path,
		std::vector<double>& vec_pos,
		std::vector<int>& vec_idx);

	//	メッシュとして保存（バイナリ）
	//	保存したものがMeshLabで開けない。どこかがおかしいが今のところ
	int save_mesh_as_ply_bin(
		std::string& path,
		std::vector<float>& vec_pos,
		std::vector<int>& vec_idx);


	//	PLYファイル読込み
	int load_mesh_as_ply(
		std::string& path,
		std::vector<double>& vec_pos,
		std::vector<double>& vec_nv,
		std::vector<int>& vec_idx);

	int load_mesh_as_ply(
		std::string& path,
		std::vector<float>& vec_pos,
		std::vector<float>& vec_nv,
		std::vector<int>& vec_idx);
};
