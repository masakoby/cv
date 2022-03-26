//
//	ply�t�@�C��
//

#include <string>
#include <vector>

#pragma once

namespace kb
{
	//	�R�����_�Q�Ƃ��ĕۑ�
	int save_pt3d_as_ply(
		std::string& path,
		std::vector<float>& v_pt,
		std::vector<unsigned char>& vcolor);
	//	�R�����_�Q�Ƃ��ĕۑ�
	int save_pt3d_as_ply(
		std::string& path,
		std::vector<float>& v_pt);

	//	�R�����_�Ƌȗ��E���ꗦ
	int save_pt3d_curvature_torsion_as_ply(
		std::string& path,
		std::vector<double>& v_pt,
		std::vector<double>& v_curvature,
		std::vector<double>& v_torsion
		);



};
