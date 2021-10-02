#include "kb_csv.h"
#include <fstream> 
#include <sstream>

int kb::load_space(std::string& path, std::vector<std::vector<std::string>>& vv)
{
	char delim = ' ';
	return kb::load_csv(path, vv, delim);
}

int kb::load_csv(std::string& path, std::vector<std::vector<std::string>>& vv, char delim = ',')
{
	// ファイルを開く
	std::ifstream f1(path);
	if (!f1.is_open())
		return -1;


	while (1) {
		//
		std::string strL1;
		std::getline(f1, strL1);

		//	データ
		std::istringstream stream(strL1);

		std::vector<std::string> v1;
		int k = 0;

		//1行のうち、文字列とコンマを分割する
		while (1) {
			std::string token;
			std::getline(stream, token, delim);
			size_t n1 = token.length();
			if (n1 == 0) {
			}
			else {
				k++;
				v1.push_back(token);
			}
			if (stream.eof() != false)
				break;
		}

		if (k > 0) {
			vv.push_back(v1);
		}

		if (f1.eof() == true)
			break;

	}

	return 0;
}

int kb::save_csv(std::string& path, std::vector<std::vector<std::string>>& vv)//, char delim=',')
{
	std::ofstream f1(path);
	if (!f1.is_open())
		return -1;

	int num_vv = vv.size();
	for (int k = 0; k < num_vv; k++) {
		int num_v = vv[k].size();
		for (int kk = 0; kk < num_v; kk++) {
			f1 << vv[k][kk] << ",";
		}
		f1 << std::endl;
	}

	return 0;
}

