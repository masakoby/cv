#include <opencv2/opencv.hpp>


#pragma once

namespace kb
{

	int chess2perspective_transform(
		std::string& dname_chess,
		std::string& path_prm,
		double ratio_preproc,
		std::vector<cv::Point2f>& v_chess,
		std::vector<cv::Point2f>& v_chess2,
		cv::Mat& matP);
};

