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
		//	�摜�ǂݍ��݁A
		int create(std::string& dname_image, std::string& key);
		int findCircles(std::string& path_image);

		//
		int create2nd(kb::Calib& calib2);

		int findCirclesGrid(
			cv::Mat& matF, 
			std::vector<cv::Point2f>& v2d_out);


		//	�L�����u���[�V����
		int calibrate();
		int calibrateFisheye();

		//	�L�����u���[�V�����ɗp�����`�F�b�J�[�{�[�h�摜�ɑ΂���
		//	�c�ݕ␳���s��
		int debug_undistort();

		//	�c�ݕ␳�̎��s
		int undistort(cv::Mat& mat1, cv::Mat& mat_out);

		//	�����p�����[�^�̓ǂݍ���
		int load_param(std::string& path_prm);

		//
		int save(std::string& path);
		int load(std::string& path);
		int load_test(std::string& path);

	public:
		//	�`�F�b�J�[�{�[�h���摜
		std::vector<cv::Mat> m_vmat1;
		//	���T�C�Y��̌��摜
		std::vector<cv::Mat> m_vmat2;
		//	�`�F�b�J�[�{�[�h���o��������������
		std::vector<int> m_vflag2;

		//	�`�F�b�J�[�{�[�h���摜�T�C�Y
		cv::Size m_szImage1;
		//	�O������̃`�F�b�J�[�{�[�h�摜�T�C�Y
		cv::Size m_szImage2;
		//	�c�ݕ␳��̉摜�T�C�Y
		cv::Size m_szImage3;

		std::vector<std::vector<cv::Point2f>> m_vv_p2d;
		std::vector<int> m_v_idx;

		//	�L�����u���[�V�����p�����[�^
		cv::Mat m_camIn;
		cv::Mat m_distCoef;
		std::vector<cv::Mat> m_vecR, m_vecT;

		//	remap�p�p�����[�^
		cv::Mat m_camIn2;
		cv::Mat m_map1, m_map2;

		//	�����p�����[�^
	public:
		//
		int m_debug;
		//	�`�F�b�J�[�{�[�h�̃p�^�[����
		cv::Size m_patternSize;
		//	�p�^�[���Ԃ̋���
		double m_step_width;

		//	�`�F�b�J�[�{�[�h���o���鎞�ɕ������������s��
		int m_mode_sm;
		//
		int m_num_max_find_circle;


		//	�L�����u���[�V�������s�����̉摜�T�C�Y
		//	�摜�T�C�Y���傫��(4000x3000)�ƁA�T�[�N�����o�Ȃǂ����s���邽��
		//	������x�A�摜�T�C�Y������������(1200x900)
		int m_pre_width;
		//	�c�ݕ␳��̉摜�T�C�Y
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
