
#include "kb_cv_matching_mser.h"


int kb::match_MSER(
	cv::Mat& mat1,
	cv::Mat& mat2,
	std::vector<cv::DMatch>& v_dm,
	std::vector<cv::KeyPoint>& v_kp1,
	std::vector<cv::KeyPoint>& v_kp2,
	int delta, //5
	int min_area, //60
	int max_area,//14400
	double max_variation,//0.25
	double min_div,//0.2
	int max_ev,//200
	double area_thres,//1.01
	double min_margin,//0.003
	int edge_blur_size//5
)
{
	std::cout << "cv::MSER::create" << std::endl;
	auto alg1 = cv::MSER::create(
		delta, //5
		min_area, //60
		max_area,//14400
		max_variation,//0.25
		min_div,//0.2
		max_ev,//200
		area_thres,//1.01
		min_margin,//0.003
		edge_blur_size//5
	);


	//	mask
	cv::Mat mask1(mat1.size(), CV_8UC1, cv::Scalar(255));
	cv::Mat mask2(mat2.size(), CV_8UC1, cv::Scalar(255));

	//特徴点抽出
	std::cout << "cv::MSER::detect" << std::endl;
	alg1->detect(mat1, v_kp1, mask1);
	alg1->detect(mat2, v_kp2, mask2);

	// 特徴記述
	std::cout << "cv::MSER::compute" << std::endl;
	cv::Mat d1, d2;
	alg1->compute(mat1, v_kp1, d1);
	alg1->compute(mat2, v_kp2, d2);

	std::cout << alg1->defaultNorm() << std::endl;

	// 対応点検索
	cv::BFMatcher matcher1(alg1->defaultNorm(), false);
	//cv::BFMatcher matcher1(cv::NORM_HAMMING, false);
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

