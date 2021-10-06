//
//	plyƒtƒ@ƒCƒ‹
//

#include <string>
#include <vector>

#pragma once

namespace kb
{
	//	‚RŽŸŒ³“_ŒQ‚Æ‚µ‚Ä•Û‘¶
	int save_pt3d_as_ply(
		std::string& path,
		std::vector<float>& v_pt,
		std::vector<unsigned char>& vcolor);
	//	‚RŽŸŒ³“_ŒQ‚Æ‚µ‚Ä•Û‘¶
	int save_pt3d_as_ply(
		std::string& path,
		std::vector<float>& v_pt);




};
