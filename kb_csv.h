#include <string>
#include <vector>

#pragma once

namespace kb
{
	//	�J���}��؂蕶���Ƃ��āA�t�@�C���ǂݍ��݂��s��
	int load_csv(std::string& path, std::vector<std::vector<std::string>>& vv, char delim);

	//	�J���}��؂蕶���Ƃ��āA�t�@�C���������݂��s��
	int save_csv(std::string& path, std::vector<std::vector<std::string>>& vv);


	//	space����؂蕶���Ƃ��āA�t�@�C���ǂݍ��݂��s��
	int load_space(std::string& path, std::vector<std::vector<std::string>>& vv);
};
