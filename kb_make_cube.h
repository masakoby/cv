#include <vector>

#pragma once

namespace kb
{
	//	�����̂̂P�̖ʂ��m�[�h���X�A�R�p�`�W���g���Đ�������
	int make_cube_1face(std::vector<double>& vec_pos, std::vector<int>& vec_idx, double length, int face0to5);

	int make_cube_1face(double vec_pos[12], double matR1[9], int vec_idx[4], double length, int face0to5);
	int make_cube_1face_v2(double vec_pos[12], double matR1[9], int vec_idx[4], double length, int face0to5);

	int dirvector_cube_1face(double vec_pos[3], int face0to5);

};