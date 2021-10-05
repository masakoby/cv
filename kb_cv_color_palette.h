#include <opencv2/opencv.hpp>

#pragma once

namespace kb
{
	//	パレットのバー作成
	int palette_bar(cv::Mat& matRGB, int type);

	//	パレットの読込み
	int load_csv_palette(std::string& path, std::vector< cv::Scalar>& palette);
};
