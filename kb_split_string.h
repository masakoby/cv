
#include <string>
#include <vector>

#pragma once

namespace kb
{
	//	���������؂蕶����p���ĕ�������
	int split_string(
		const std::string& strL1, 
		char delim, 
		std::vector<std::string>& v_str1
	);

	//	�p�X�����A�f�B���N�g�����ƃt�@�C�����ɕ�������
	void split_path(std::string& path, std::string& dirname, std::string& filename);
	void split_path(std::string& path, std::string& dirname, std::string& filetitle, std::string& fileext);
	//
	void split_filename(std::string& filename, std::string& filetitle, std::string& fext);

};

