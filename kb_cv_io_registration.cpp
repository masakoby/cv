#include "kb_cv_io_registration.h"
#include "kb_csv.h"
#include <direct.h>

int kb::save_corresponding_points(
	std::string& dname_output,
	std::string& filetitle,
	std::vector<cv::Point2f>& mp1,
	std::vector<cv::Point2f>& mp2,
	double base_ratio_reduce
	)
{
	double base_ratio = 1.0 / base_ratio_reduce;

	std::string dname_output2 = dname_output + filetitle + "\\";
	std::string path_pt1 = dname_output2 + "1-" + filetitle + "_cpt.txt";
	std::string path_pt2 = dname_output2 + "2-" + filetitle + "_cpt.txt";
	_mkdir(dname_output2.c_str());
	{
		std::ofstream file(path_pt1);
		int num = mp1.size();
		for (int i = 0; i < num; i++) {
			file << mp1[i].x * base_ratio << " " << mp1[i].y * base_ratio << " 64 0" << std::endl;
		}
	}
	{
		std::ofstream file(path_pt2);
		int num = mp2.size();
		for (int i = 0; i < num; i++) {
			file << mp2[i].x * base_ratio << " " << mp2[i].y * base_ratio << " 64 0" << std::endl;
		}
	}
	return 0;
}

int kb::load_corresponding_points(
	std::string& dname_output,
	std::string& filetitle,
	std::vector<cv::Point2f>& mp1,
	std::vector<cv::Point2f>& mp2
)
{
	std::string dname_output2 = dname_output + filetitle + "\\";
	std::string path_pt1 = dname_output2 + "1-" + filetitle + "_cpt.txt";
	std::string path_pt2 = dname_output2 + "2-" + filetitle + "_cpt.txt";

	std::vector<std::vector<std::string>> vv1, vv2;
	kb::load_space(path_pt1, vv1);
	kb::load_space(path_pt2, vv2);

	{
		int num_vv1 = vv1.size();
		for (int i = 0; i < num_vv1; i++) {
			int num_v = vv1[i].size();
			if (num_v < 4)
				continue;
			cv::Point2f p;
			p.x = std::stof(vv1[i][0]);
			p.y = std::stof(vv1[i][1]);
			mp1.push_back(p);
		}
	}
	{
		int num_vv2 = vv2.size();
		for (int i = 0; i < num_vv2; i++) {
			int num_v = vv2[i].size();
			if (num_v < 4)
				continue;
			cv::Point2f p;
			p.x = std::stof(vv2[i][0]);
			p.y = std::stof(vv2[i][1]);
			mp2.push_back(p);
		}
	}
	return 0;
}
