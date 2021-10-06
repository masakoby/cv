#include <string>
#include <vector>

#pragma once

namespace kb
{
	//	PLY�t�@�C���ۑ�
	int save_mesh_as_ply(
		std::string& path,
		std::vector<float>& vec_pos,
		std::vector<int>& vec_idx);
	int save_mesh_as_ply(
		std::string& path,
		std::vector<double>& vec_pos,
		std::vector<int>& vec_idx);

	//	���b�V���Ƃ��ĕۑ��i�o�C�i���j
	//	�ۑ��������̂�MeshLab�ŊJ���Ȃ��B�ǂ������������������̂Ƃ���
	int save_mesh_as_ply_bin(
		std::string& path,
		std::vector<float>& vec_pos,
		std::vector<int>& vec_idx);


	//	PLY�t�@�C���Ǎ���
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
