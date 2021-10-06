
#include "kb_cv_matching_sift.h"
#include <opencv2/xfeatures2d.hpp>

int kb::match_sift(
	cv::Mat& mat1,
	cv::Mat& mat2,
	std::vector<cv::DMatch>& v_dm,
	std::vector<cv::KeyPoint>& v_kp1,
	std::vector<cv::KeyPoint>& v_kp2,

	double contrast_thr,
	double edge_thr,
	double sigma
)
{
	auto alg1 = cv::xfeatures2d::SIFT::create(0, 3, contrast_thr, edge_thr, sigma);

	//	mask
	cv::Mat mask1(mat1.size(), CV_8UC1, cv::Scalar(255));
	cv::Mat mask2(mat2.size(), CV_8UC1, cv::Scalar(255));

	//特徴点抽出
	alg1->detect(mat1, v_kp1, mask1);
	alg1->detect(mat2, v_kp2, mask2);

	// 特徴記述
	cv::Mat d1, d2;
	alg1->compute(mat1, v_kp1, d1);
	alg1->compute(mat2, v_kp2, d2);

	// 対応点検索
	cv::BFMatcher matcher1(alg1->defaultNorm(), false);
	std::vector<cv::DMatch> match12, match21;
	matcher1.match(d1, d2, match12);
	matcher1.match(d2, d1, match21);

	//	双方向のみ残す
	for (size_t i = 0; i < match12.size(); i++)
	{
		cv::DMatch forward = match12[i];
		cv::DMatch backward = match21[forward.trainIdx];
		if (backward.trainIdx == forward.queryIdx)
			v_dm.push_back(forward);
	}

	return 0;
}

