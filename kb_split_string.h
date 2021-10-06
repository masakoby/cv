
#include <string>
#include <vector>

#pragma once

namespace kb
{
	//	文字列を区切り文字を用いて分離する
	int split_string(
		const std::string& strL1, 
		char delim, 
		std::vector<std::string>& v_str1
	);

	//	パス名を、ディレクトリ名とファイル名に分離する
	void split_path(std::string& path, std::string& dirname, std::string& filename);
	void split_path(std::string& path, std::string& dirname, std::string& filetitle, std::string& fileext);
	//
	void split_filename(std::string& filename, std::string& filetitle, std::string& fext);

};

