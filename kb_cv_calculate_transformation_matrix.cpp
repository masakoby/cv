#include "kb_cv_calculate_transformation_matrix.h"
#include "kb_cv_resize.h"

int kb::calculate_affine_transformation_matrix(
	std::vector<cv::Point2f>& mp1,
	std::vector<cv::Point2f>& mp2,
	cv::Mat& matAf_3x3,
	double ratio_reduce
)
{
	if(ratio_reduce>0.0){

		std::vector<cv::Point2f> mp1x, mp2x;
		kb::resize(mp1, mp1x, ratio_reduce);
		kb::resize(mp2, mp2x, ratio_reduce);
		cv::Mat matAf = cv::estimateAffinePartial2D(mp1x, mp2x);

		matAf_3x3 = cv::Mat::eye(3, 3, CV_64F);
		matAf_3x3.at<double>(0, 0) = matAf.at<double>(0, 0);
		matAf_3x3.at<double>(0, 1) = matAf.at<double>(0, 1);
		matAf_3x3.at<double>(0, 2) = matAf.at<double>(0, 2);
		matAf_3x3.at<double>(1, 0) = matAf.at<double>(1, 0);
		matAf_3x3.at<double>(1, 1) = matAf.at<double>(1, 1);
		matAf_3x3.at<double>(1, 2) = matAf.at<double>(1, 2);
	}
	else {
		cv::Mat matAf = cv::estimateAffinePartial2D(mp1, mp2);

		matAf_3x3 = cv::Mat::eye(3, 3, CV_64F);
		matAf_3x3.at<double>(0, 0) = matAf.at<double>(0, 0);
		matAf_3x3.at<double>(0, 1) = matAf.at<double>(0, 1);
		matAf_3x3.at<double>(0, 2) = matAf.at<double>(0, 2);
		matAf_3x3.at<double>(1, 0) = matAf.at<double>(1, 0);
		matAf_3x3.at<double>(1, 1) = matAf.at<double>(1, 1);
		matAf_3x3.at<double>(1, 2) = matAf.at<double>(1, 2);

	}
	return 0;
}
