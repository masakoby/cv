#include "kb_cv_matmul_3x3.h"

int kb::matmul_3x3(cv::Mat& matAf_64F, std::vector<cv::Point2f>& vp, std::vector<cv::Point2f>& vp_out)
{
	cv::Size sz = matAf_64F.size();
	if (sz.width < 3 || sz.height < 2)
		return -1;

	int num = vp.size();
	vp_out.resize(num);
	for (int k = 0; k < num; k++) {
		vp_out[k].x = matAf_64F.at<double>(0, 0) * vp[k].x + matAf_64F.at<double>(0, 1) * vp[k].y + matAf_64F.at<double>(0, 2);
		vp_out[k].y = matAf_64F.at<double>(1, 0) * vp[k].x + matAf_64F.at<double>(1, 1) * vp[k].y + matAf_64F.at<double>(1, 2);
	}
	return 0;
}

int kb::matmul_3x3(cv::Mat& matAf_64F, cv::Point2f& p, cv::Point2f& p_out)
{
	cv::Size sz = matAf_64F.size();
	if (sz.width < 3 || sz.height < 2)
		return -1;

	p_out.x = matAf_64F.at<double>(0, 0) * p.x + matAf_64F.at<double>(0, 1) * p.y + matAf_64F.at<double>(0, 2);
	p_out.y = matAf_64F.at<double>(1, 0) * p.x + matAf_64F.at<double>(1, 1) * p.y + matAf_64F.at<double>(1, 2);
	return 0;
}

int kb::homogeneous_transformation_3x3(cv::Mat& matAf_64F, std::vector<cv::Point2f>& vp, std::vector<cv::Point2f>& vp_out)
{
	cv::Size sz = matAf_64F.size();
	if (sz.width < 3 || sz.height < 3)
		return -1;

	int num = vp.size();
	vp_out.resize(num);
	for (int k = 0; k < num; k++) {
		double z = matAf_64F.at<double>(2, 0) * vp[k].x + matAf_64F.at<double>(2, 1) * vp[k].y + matAf_64F.at<double>(2, 2);

		vp_out[k].x = (matAf_64F.at<double>(0, 0) * vp[k].x + matAf_64F.at<double>(0, 1) * vp[k].y + matAf_64F.at<double>(0, 2)) / z;
		vp_out[k].y = (matAf_64F.at<double>(1, 0) * vp[k].x + matAf_64F.at<double>(1, 1) * vp[k].y + matAf_64F.at<double>(1, 2)) / z;
	}
	return 0;
}

int kb::homogeneous_transformation_3x3(cv::Mat& matAf_64F, cv::Point2f& p, cv::Point2f& p_out)
{
	cv::Size sz = matAf_64F.size();
	if (sz.width < 3 || sz.height < 3)
		return -1;

	double z = matAf_64F.at<double>(2, 0) * p.x + matAf_64F.at<double>(2, 1) * p.y + matAf_64F.at<double>(2, 2);

	p_out.x = (matAf_64F.at<double>(0, 0) * p.x + matAf_64F.at<double>(0, 1) * p.y + matAf_64F.at<double>(0, 2)) / z;
	p_out.y = (matAf_64F.at<double>(1, 0) * p.x + matAf_64F.at<double>(1, 1) * p.y + matAf_64F.at<double>(1, 2)) / z;

	return 0;
}

