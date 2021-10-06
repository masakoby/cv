#include <vector>
#include <string>

#include <opencv2/opencv.hpp>

#pragma once

namespace kb
{
	//	病理スライドの位置合わせ処理ツールに読み込ませる対応点
	//	AAAA\1-AAAA_cpt.txt
	//	AAAA\2-AAAA_cpt.txt

	//	
	int save_corresponding_points(
		std::string& dname_output,
		std::string& filetitle,
		std::vector<cv::Point2f>& mp1,
		std::vector<cv::Point2f>& mp2,
		double base_ratio	//	病理スライド画像から全体画像を得た時の縮小倍率
	);

	int load_corresponding_points(
		std::string& dname_output,
		std::string& filetitle,
		std::vector<cv::Point2f>& mp1,
		std::vector<cv::Point2f>& mp2
	);

};
