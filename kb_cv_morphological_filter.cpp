#include "kb_cv_morphological_filter.h"

int kb::opening(cv::Mat& mat1, cv::Mat& mat1_out, int num_opening)
{

}

int kb::closing(cv::Mat& mat1, cv::Mat& mat1_out, int num_closing)
{
	cv::Mat mat2;
	cv::dilate(mat1, mat2, cv::Mat(), cv::Point(-1, -1), num_closing);

	cv::erode(mat2, mat1_out, cv::Mat(), cv::Point(-1, -1), num_closing);
	return 0;
}

