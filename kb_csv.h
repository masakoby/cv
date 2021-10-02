#include <string>
#include <vector>

#pragma once

namespace kb
{
	//	カンマ区切り文字として、ファイル読み込みを行う
	int load_csv(std::string& path, std::vector<std::vector<std::string>>& vv, char delim);

	//	カンマ区切り文字として、ファイル書き込みを行う
	int save_csv(std::string& path, std::vector<std::vector<std::string>>& vv);


	//	spaceが区切り文字として、ファイル読み込みを行う
	int load_space(std::string& path, std::vector<std::vector<std::string>>& vv);
};
