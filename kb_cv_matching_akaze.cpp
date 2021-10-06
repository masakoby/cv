#include "kb_cv_matching_akaze.h"

int kb::match_akaze(
	cv::Mat& mat1,
	cv::Mat& mat2,
	std::vector<cv::DMatch>& v_dm,
	std::vector<cv::KeyPoint>& v_kp1,
	std::vector<cv::KeyPoint>& v_kp2,

	double thr,
	int mode_matching
)
{
	auto alg1 = cv::AKAZE::create(cv::AKAZE::DESCRIPTOR_MLDB, 0, 3, thr);

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
	//	d1: query=source
	//	d2: train=target

	matcher1.match(d2, d1, match21);
	//	d2: query
	//	d1: train

	//	双方向のみ残す
	if (mode_matching == 0) {
		for (size_t i = 0; i < match12.size(); i++)
		{
			cv::DMatch forward = match12[i];
			cv::DMatch backward = match21[forward.trainIdx];
			//	1: forward.queryIdx(source)
			//	2: forward.trainIdx(target)
			//	forward: 1->2
			//
			if (backward.trainIdx == forward.queryIdx)
				v_dm.push_back(forward);
		}
	}else{
		v_dm = match12;
		for (size_t i = 0; i < match21.size(); i++)
		{
			cv::DMatch forward = match21[i];
			cv::DMatch backward = match12[forward.trainIdx];
			//
			if (backward.trainIdx == forward.queryIdx) {
			}
			else {
				cv::DMatch f2= forward;
				f2.trainIdx = forward.queryIdx;
				f2.queryIdx = forward.trainIdx;

				v_dm.push_back(f2);
			}
		}
	}

	return 0;
}
