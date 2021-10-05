#include <vector>
#include <opencv2/opencv.hpp>

#pragma once

namespace kb
{

	//	投影変換行列リストを使った順方向参照による画像合成
	//	順方向参照なので、合成画像において画素が抜けて表示される可能性がある
	//	処理がシンプルで、様子見の処理としては適している
	int compose_images_forward(
		std::vector<cv::Mat>& v_images,
		std::vector<cv::Mat>& v_af,
		double rangex[2], double rangey[2],
		cv::Mat& matV
	);

	int compose_images_backward(
		std::vector<cv::Mat>& v_images,
		std::vector<cv::Mat>& v_af,
		double rangex[2], double rangey[2],
		cv::Mat& matV
	);
	int compose_images_backward_v2(
		std::vector<cv::Mat>& v_images,
		std::vector<cv::Mat>& v_af,
		double rangex[2], double rangey[2],
		cv::Mat& matV,
		double ratio_sigma
	);

	//	
	int compose_matP(
		std::vector<cv::Mat>& v_P_neighbor,
		cv::Size& sz0,
		std::vector<cv::Mat>& v_P_out,
		double rangex_out[2],
		double rangey_out[2],
		cv::Mat matEye
	);



	int update_link0(
		cv::Size& sz0,
		std::vector<cv::Mat>& v_P1,
		std::vector<cv::Point2f>& v_pt_out
	);
	int update_link(
		cv::Size& sz0,
		std::vector<cv::Mat>& v_P1,
		double rangex1[2], double rangey1[2],
		std::vector<int>& v_link,
		std::vector<cv::Point2f>& v_pt_out
	);

	//	追跡経路の可視化
	//		全体画像に対する投影変換行列の配列があって、
	//		それが追跡順に並んでいて、
	//		投影変換行列によって個々の画像が全体画像にマッピングされているとき、
	//		全体画像のなかで個々の画像中心を結んだら、追跡経路を可視化できる。
	int draw_trackingline(
		cv::Mat& matV,
		cv::Size& sz0,
		std::vector<cv::Mat>& v_P1,
		double rangex1[2], double rangey1[2]
	);
	int draw_trackingline(
		cv::Mat& matV,
		std::vector<cv::Point2f>& v_pt,
		std::vector<int>& vflag,
		double rangex1[2], double rangey1[2],
		std::vector<int>& v_link,
		cv::Scalar color_line
	);

};
