#include <opencv2/opencv.hpp>

#pragma once

//	B,G,R,color name
namespace kb
{
	//	パレットの読込み
	int load_csv_palette(std::string& path, std::vector< cv::Scalar>& palette);
	int load_csv_palette(std::string& path, std::vector< cv::Scalar>& palette, std::vector<std::string>& vname);
};
