//
//	plyファイル
//

#include <string>
#include <vector>

#pragma once

namespace kb
{
	//	３次元点群として保存
	int save_pt3d_as_ply(
		std::string& path,
		std::vector<float>& v_pt,
		std::vector<unsigned char>& vcolor);
	//	３次元点群として保存
	int save_pt3d_as_ply(
		std::string& path,
		std::vector<float>& v_pt);




};
