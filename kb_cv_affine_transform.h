
#include <opencv2/opencv.hpp>

#include "lx_prm_RANSAC.h"

namespace kb
{


	//--------------------------------------------
	//	RANSAC, transformation matrix

	int calculate_affine(
		std::vector<cv::DMatch>& v_dm,
		std::vector<cv::KeyPoint>& v_kp1,
		std::vector<cv::KeyPoint>& v_kp2,

		cv::Mat& matAf,
		std::vector<cv::Point2f>& mp1_inlier,
		std::vector<cv::Point2f>& mp2_inlier,

		CPrm_RANSAC& prm,
		cv::Mat& mat1,
		cv::Mat& mat2,
		cv::Mat& mat12_out,
		int& key1
	);


	//	RANSAC
	int calculate_affine(
		std::vector<cv::Point2f>& mp1,
		std::vector<cv::Point2f>& mp2,
		cv::Size& sz_img,
		cv::Mat& matAf,
		std::vector<cv::Point2f>& mp1_inlier,
		std::vector<cv::Point2f>& mp2_inlier,
		double threshold_dis1,
		int thres_max_valid_cnt,
		int RANSAC_iter_num,
		int numThread,
		double det_min,
		double det_max,
		double ratio_area,
		int mode //= 0
	);

};
