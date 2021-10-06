#include "kb_split_string.h"
#include <iostream>
#include <sstream>



int kb::split_string(const std::string& strL1, char delim, std::vector<std::string>& v_str1)
{
	//	データ
	std::istringstream stream(strL1);
	int k = 0;

	//1行のうち、文字列と(コンマ)を分割する
	while (1) {
		std::string token;
		std::getline(stream, token, delim);// '_');
		size_t n1 = token.length();
		if (n1 == 0) {
		}
		else {
			k++;
			v_str1.push_back(token);
		}
		if (stream.eof() != false)
			break;
	}
	return k;
}

void kb::split_path(std::string& path, std::string& dirname, std::string& filename)
{
	int nn2 = path.length();
	int k1 = path.find_last_of("\\");
	int k2 = path.find_last_of("/");
	int kk = k1;	if (kk < k2) { kk = k2; }
	filename = path.substr(kk + 1, nn2 - kk - 1);

	dirname = path.substr(0, kk + 1);
}

void kb::split_path(std::string& path, std::string& dirname, std::string& filetitle, std::string& fext)
{
	std::string filename;
	{
		int nn2 = path.length();
		int k1 = path.find_last_of("\\");
		int k2 = path.find_last_of("/");
		int kk = k1;	if (kk < k2) { kk = k2; }


		filename = path.substr(kk + 1, nn2 - kk - 1);
		dirname = path.substr(0, kk + 1);
	}

	{
		int nn2 = filename.length();
		int k1 = filename.find_last_of(".");

		if (k1 >= 0) {
			filetitle = filename.substr(0, k1);
			fext = filename.substr(k1 + 1, nn2 - k1 - 1);
		}
		else {
			filetitle = filename;
		}
	}

}

void kb::split_filename(std::string& filename, std::string& filetitle, std::string& fext)
{
	int nn2 = filename.length();
	int k1 = filename.find_last_of(".");

	if (k1 >= 0) {
		filetitle = filename.substr(0, k1);
		fext = filename.substr(k1 + 1, nn2 - k1 - 1);
	}
	else {
		filetitle = filename;
	}
}
