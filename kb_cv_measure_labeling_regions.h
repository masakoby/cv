#include <opencv2/opencv.hpp>

#include <vector>

#pragma once

namespace kb
{

	//	�ʐ�
	int measureSquare(
		cv::Mat& matLabel,
		int numLabel,
		std::vector<int>& oVec
	);

	//	�d�S
	int measureBarycenter(
		cv::Mat& matLabel,
		int numLabel,
		std::vector<int>& vecSquare,
		std::vector<double>& vecPos
	);

	//	���ϋP�x
	int measureAverage_RGB(
		cv::Mat& matLabel,
		int numLabel,
		cv::Mat& matValueRGB,
		std::vector<int>& vecSquare,
		std::vector<double>& vecAverageRGB
	);
	//	���ϋP�x�ƕ��U
	int measureAverageVariance_RGB(
		cv::Mat& matLabel,
		int numLabel,
		cv::Mat& matValueRGB,
		std::vector<int>& vecSquare,
		std::vector<double>& vecAverage,
		std::vector<double>& vecVariance
	);

	//	�o�E���f�B���O�{�b�N�X
	int measureBoundingBox(
		cv::Mat& matL1, int num_label,
		std::vector<int>& squares,
		std::vector<cv::Point>& vecPtsMin,
		std::vector<cv::Point>& vecPtsMax
	);

	//	�o�E���f�B���O�{�b�N�X�i�΂߁j
	int measureBoundingBox_by_PCA(
		cv::Mat& matL1, int num_label,
		std::vector<cv::Point2f>& v_pos,// �d�S
		std::vector<cv::Point2f>& v_dir,// �̈�̎厲����
		std::vector<cv::Point2f>& v_pos2,//�@�厲�����ɂ�����d�S����̍ŉ��ʒu�i���x�����~�Q�j
		std::vector<cv::Point2f>& v_pos4//�o�E���f�B���O�{�b�N�X�i���x�����~�S�j
	);

	//	���x���̈悲�Ƃ̂R�����q�X�g�O�����擾
	int measureHistogram3D_RGB(
		cv::Mat& matLabel,
		int numLabel,
		cv::Mat& matValueRGB,
		int num_bin,//histogram�̃r����
		std::vector<float>& hist
	);

	//	���x���̈�Ԃ̋������v��
	int measureMinimumDistance(
		cv::Mat& matLabel,
		int numLabel,
		std::vector<float>& oVec	//	���x�����~���x����

	);

	int measureContours(
		cv::Mat& matLabel,
		int numLabel,
		std::vector<std::vector<std::vector<cv::Point>>>& vv_contours
		);

};
