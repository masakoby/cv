#include "kb_cv_copyTo.h"

//	領域がはみ出てもコピーする
int kb::copyTo_8UC3(cv::Mat& mat1, cv::Rect& rect, cv::Mat& mat2, cv::Vec3b bk)
{
	cv::Size sz1 = mat1.size();
	cv::Point p2(rect.x, rect.y);
	cv::Size sz2 = rect.size();

	mat2 = cv::Mat(sz2, CV_8UC3, bk);
	for (int j = 0; j < sz2.height; j++) {
		int j1 = j + p2.y;
		if (j1 < 0 || sz1.height <= j1)
			continue;

		for (int i = 0; i < sz2.width; i++) {
			int i1 = i + p2.x;
			if (i1 < 0 || sz1.width <= i1)
				continue;
			mat2.at<cv::Vec3b>(j, i) = mat1.at<cv::Vec3b>(j1, i1);
		}
	}

	return 0;
}

//	マスク領域のみコピーする
//	領域がはみ出てもコピーする
int kb::copyTo_8UC3(cv::Mat& mat1, cv::Rect& rect, cv::Mat& mask, cv::Mat& mat2, cv::Vec3b bk)
{
	cv::Size sz1 = mat1.size();
	cv::Point p2(rect.x, rect.y);
	cv::Size sz2 = rect.size();

	cv::Size sz1m = mask.size();
	mat2 = cv::Mat(sz2, CV_8UC3, bk);

	if (sz1m == sz1) {
		for (int j = 0; j < sz2.height; j++) {
			int j1 = j + p2.y;
			if (j1 < 0 || sz1.height <= j1)
				continue;

			for (int i = 0; i < sz2.width; i++) {
				int i1 = i + p2.x;
				if (i1 < 0 || sz1.width <= i1)
					continue;
				if (mask.at<unsigned char>(j1, i1) == 0)
					continue;
				mat2.at<cv::Vec3b>(j, i) = mat1.at<cv::Vec3b>(j1, i1);
			}
		}
	}
	else {
		for (int j = 0; j < sz2.height; j++) {
			int j1 = j + p2.y;
			if (j1 < 0 || sz1.height <= j1)
				continue;

			for (int i = 0; i < sz2.width; i++) {
				int i1 = i + p2.x;
				if (i1 < 0 || sz1.width <= i1)
					continue;
				mat2.at<cv::Vec3b>(j, i) = mat1.at<cv::Vec3b>(j1, i1);
			}
		}
	}

	return 0;
}

//	マスク領域のみコピーする
//	領域がはみ出てもコピーする
int kb::copyTo_8UC1(cv::Mat& mat1, cv::Mat& mask1, cv::Mat& mat2, cv::Point& pt2)
{
	cv::Size sz1 = mat1.size();
	cv::Size sz2 = mat2.size();

	cv::Size sz1m = mask1.size();

	if (sz1m == sz1) {
		for (int j = 0; j < sz1.height; j++) {
			int j2 = j + pt2.y;
			if (j2 < 0 || sz2.height <= j2)
				continue;

			for (int i = 0; i < sz1.width; i++) {
				int i2 = i + pt2.x;
				if (i2 < 0 || sz2.width <= i2)
					continue;
				if (mask1.at<unsigned char>(j, i) == 0)
					continue;
				mat2.at<unsigned char>(j2, i2) = mat1.at<unsigned char>(j, i);
			}
		}
	}
	else {
		for (int j = 0; j < sz1.height; j++) {
			int j2 = j + pt2.y;
			if (j2 < 0 || sz2.height <= j2)
				continue;

			for (int i = 0; i < sz1.width; i++) {
				int i2 = i + pt2.x;
				if (i2 < 0 || sz2.width <= i2)
					continue;
				mat2.at<unsigned char>(j2, i2) = mat1.at<unsigned char>(j, i);
			}
		}
	}

	return 0;
}

//	領域がはみ出てもコピーする
int kb::copyTo_8UC1(cv::Mat& mat1, cv::Rect& rect, cv::Mat& mat2)
{
	cv::Size sz1 = mat1.size();
	cv::Point p2(rect.x, rect.y);
	cv::Size sz2 = rect.size();

	mat2 = cv::Mat(sz2, CV_8UC1, cv::Scalar(0));
	for (int j = 0; j < sz2.height; j++) {
		int j1 = j + p2.y;
		if (j1 < 0 || sz1.height <= j1)
			continue;

		for (int i = 0; i < sz2.width; i++) {
			int i1 = i + p2.x;
			if (i1 < 0 || sz1.width <= i1)
				continue;
			mat2.at<unsigned char>(j, i) = mat1.at<unsigned char>(j1, i1);
		}
	}

	return 0;
}
