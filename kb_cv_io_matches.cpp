#include "kb_cv_io_matches.h"

//-----------------------------------------------------------------------------------------------

int kb::save_pt2d_pair(std::string& path, std::vector<cv::Point2f>& vec_pts1, std::vector<cv::Point2f>& vec_pts2)
{
	int num1 = vec_pts1.size();
	int num2 = vec_pts2.size();
	if (num1 > num2) {
		num1 = num2;
	}

	std::ofstream file(path.c_str());
	if (file.is_open() == false)
		return -1;

	file.precision(10);

	file << "#pt2d_pair " << num1 << std::endl;

	for (int i = 0; i < num1; i++) {
		file << vec_pts1[i].x << " " << vec_pts1[i].y << " " << vec_pts2[i].x << " " << vec_pts2[i].y << std::endl;
	}

	return 0;
}

int kb::load_pt2d_pair(std::string& path, std::vector<cv::Point2f>& vec_pts1, std::vector<cv::Point2f>& vec_pts2)
{
	std::ifstream file(path.c_str());
	if (file.is_open() == false)
		return -1;

	std::string str1;
	file >> str1;
	int num = 0;
	file >> num;

	for (int i = 0; i < num; i++) {
		{
			float x = 0; file >> x;
			float y = 0; file >> y;

			vec_pts1.push_back(cv::Point2f(x, y));
		}
		{
			float x = 0; file >> x;
			float y = 0; file >> y;

			vec_pts2.push_back(cv::Point2f(x, y));
		}
	}

	return 0;
}
