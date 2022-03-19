#include <opencv2/opencv.hpp>

#pragma once

namespace kb {
	int read(std::string& path_prm, cv::CirclesGridFinderParameters& prm);
	int read(std::string& path_prm, cv::SimpleBlobDetector::Params& prm);
	int calib_fisheye(int argc, char* argv[]);
	int undistort_fisheye(int argc, char* argv[]);
	int undistort_fisheye2(int argc, char* argv[]);
	std::vector<int> getRandomNumbers(int num);

	int findCirclesGrid(cv::Mat& matF,
		cv::Size patternSize,
		std::vector<cv::Point2f>& vec_p2d_out
	);
	int findCirclesGrid2(cv::Mat& matF,
		cv::Size patternSize,
		std::vector<cv::Point2f>& vec_p2d_out
	);
	int findCirclesGrid(
		cv::Mat& matF_in,
		cv::Size patternSize,
		std::vector<cv::Point2f>& vec_p2d_out,
		double rx, double ry
	);

	int corner4(
		std::vector<cv::Point2f>& vec_p2d, 
		cv::Size patternSize,
		cv::Point2f p_out[4]
		);


	class Calib
	{
	public:
		Calib()
		{
			m_debug = 0;

			m_patternSize = cv::Size(7, 5);
			m_pre_width = 1200;
			m_step_width = 4.0;

			m_num_max_find_circle = 200;

			m_num_iter = 30;
			m_eps = 0.00001;

			m_ratio_pre_width = 2.0;

			//m_prm_c.minDensity = 10;
			m_prm_c.minDensity = 5;
			m_prm_c.densityNeighborhoodSize = cv::Size2f(16, 16);
			//m_prm_c.densityNeighborhoodSize = cv::Size2f(8, 8);
			//m_prm_c.minDistanceToAddKeypoint = 20;
			m_prm_c.minDistanceToAddKeypoint = 10;
			m_prm_c.kmeansAttempts = 100;
			m_prm_c.convexHullFactor = 1.1f;
			m_prm_c.keypointScale = 1;

			m_prm_c.minGraphConfidence = 9;
			m_prm_c.vertexGain = 1;
			m_prm_c.vertexPenalty = -0.6f;
			//m_prm_c.vertexPenalty = -0.3f;
			m_prm_c.edgeGain = 1;
			m_prm_c.edgePenalty = -0.6f;
			//m_prm_c.edgePenalty = -0.3f;
			m_prm_c.existingVertexGain = 10000;

			m_prm_c.minRNGEdgeSwitchDist = 5.f;
			m_prm_c.gridType = cv::CirclesGridFinderParameters::GridType::SYMMETRIC_GRID;

			//m_prm_c.squareSize = 1.0f;
			//m_prm_c.maxRectifiedDistance = squareSize / 2.0f;

			m_prm_blob.filterByCircularity = true;
			m_prm_blob.minCircularity = 0.5f;
			m_prm_blob.maxCircularity = 2.0f;

			//m_alpha = 1.0;
			m_alpha = 0.5;
		}

		//
		//	画像読み込み、
		int create(std::string& dname_image, std::string& key);
		int findCircles(std::string& path_image);

		//
		int create2nd(kb::Calib& calib2);

		int findCirclesGrid(
			cv::Mat& matF, 
			std::vector<cv::Point2f>& v2d_out);


		//	キャリブレーション
		int calibrate();
		int calibrateFisheye();

		//	キャリブレーションに用いたチェッカーボード画像に対して
		//	歪み補正を行う
		int debug_undistort();

		//	歪み補正の実行
		int undistort(cv::Mat& mat1, cv::Mat& mat_out);

		//	処理パラメータの読み込み
		int load_param(std::string& path_prm);

		//
		int save(std::string& path);
		int load(std::string& path);
		int load_test(std::string& path);

	public:
		//	チェッカーボード原画像
		std::vector<cv::Mat> m_vmat1;
		//	リサイズ後の原画像
		std::vector<cv::Mat> m_vmat2;
		//	チェッカーボード検出が成功したもの
		std::vector<int> m_vflag2;

		//	チェッカーボード原画像サイズ
		cv::Size m_szImage1;
		//	前処理後のチェッカーボード画像サイズ
		cv::Size m_szImage2;
		//	歪み補正後の画像サイズ
		cv::Size m_szImage3;

		std::vector<std::vector<cv::Point2f>> m_vv_p2d;
		std::vector<int> m_v_idx;

		//	キャリブレーションパラメータ
		cv::Mat m_camIn;
		cv::Mat m_distCoef;
		std::vector<cv::Mat> m_vecR, m_vecT;

		//	remap用パラメータ
		cv::Mat m_camIn2;
		cv::Mat m_map1, m_map2;

		//	処理パラメータ
	public:
		//
		int m_debug;
		//	チェッカーボードのパターン個数
		cv::Size m_patternSize;
		//	パターン間の距離
		double m_step_width;

		//	チェッカーボード検出する時に平滑化処理を行う
		int m_mode_sm;
		//
		int m_num_max_find_circle;


		//	キャリブレーションを行う時の画像サイズ
		//	画像サイズが大きい(4000x3000)と、サークル検出などが失敗するため
		//	ある程度、画像サイズを小さくする(1200x900)
		int m_pre_width;
		//	歪み補正後の画像サイズ
		double m_ratio_pre_width;

		int m_num_iter;// = 30;
		double m_eps;// = 0.00001;

		double m_alpha;
		//
		cv::CirclesGridFinderParameters m_prm_c;
		//
		cv::SimpleBlobDetector::Params m_prm_blob;

	};
};
