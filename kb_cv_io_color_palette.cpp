#include "kb_cv_io_color_palette.h"
#include "kb_csv.h"

//	�p���b�g�̓Ǎ���
int kb::load_csv_palette(std::string& path, std::vector< cv::Scalar>& palette)
{
	//	�J���}��؂蕶���Ƃ��āA�t�@�C���ǂݍ��݂��s��
	char delim = ',';
	std::vector<std::vector<std::string>> vv;
	kb::load_csv(path, vv, delim);

	int num=vv.size();
	std::cout <<"load_csv_palette: "<< num << std::endl;
	for (int k = 0; k < num; k++) {
		int num_k = vv[k].size();
		if (num_k < 3)
			continue;
		int r = std::stoi(vv[k][2]);
		int g = std::stoi(vv[k][1]);
		int b = std::stoi(vv[k][0]);

		cv::Scalar color(b,g,r);
		palette.push_back(color);
	}

	return 0;
}

//	�p���b�g�̓Ǎ���
int kb::load_csv_palette(std::string& path, std::vector< cv::Scalar>& palette, std::vector<std::string>& vname)
{
	//	�J���}��؂蕶���Ƃ��āA�t�@�C���ǂݍ��݂��s��
	char delim = ',';
	std::vector<std::vector<std::string>> vv;
	kb::load_csv(path, vv, delim);

	int num = vv.size();
	std::cout << "load_csv_palette: " << num << std::endl;
	for (int k = 0; k < num; k++) {
		int num_k = vv[k].size();
		if (num_k < 3)
			continue;
		int r = std::stoi(vv[k][2]);
		int g = std::stoi(vv[k][1]);
		int b = std::stoi(vv[k][0]);

		cv::Scalar color(b, g, r);
		palette.push_back(color);

		if (num_k >= 4) {
			vname.push_back(vv[k][3]);
		}
		else {
			vname.push_back("");
		}
	}

	return 0;
}
