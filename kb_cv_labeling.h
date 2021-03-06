#include <opencv2/opencv.hpp>
#include <vector>

#pragma once

namespace kb
{
	int labeling_8n(
		cv::Mat& mat1,
		cv::Mat& matLabel,
		int	iDel
		);
	int labeling_4n(
		cv::Mat& mat1,
		cv::Mat& matL,
		int	iDel
	);
	int labeling_8n(
		cv::Mat& mat1,
		cv::Mat& matL,
		int	iDel,
		std::vector<int>& squares,
		std::vector<cv::Point2f>& centers,
		std::vector<cv::Point>& vecPtsMin,
		std::vector<cv::Point>& vecPtsMax
	);
	int labeling_4n(
		cv::Mat& mat1,
		cv::Mat& matL,
		int	iDel,
		std::vector<int>& squares,
		std::vector<cv::Point2f>& centers,
		std::vector<cv::Point>& vecPtsMin,
		std::vector<cv::Point>& vecPtsMax
	);

	//
	void updateLabelingLUT(std::vector<int>& lutLabel);

	//
	int visualize(
		cv::Mat& matLabel,
		cv::Mat& matV
		);

	//	指定したラベル番号の領域を２値画像として取得する
	int pickup_labeling_area(cv::Mat& matL, cv::Mat& mask8U, int label);





};
