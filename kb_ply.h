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




};
