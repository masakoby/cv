#include "kb_cv_paste.h"

int kb::pasteTo(cv::Mat& matBase, cv::Mat& matOver, cv::Mat& matP, cv::Mat& matOut, int mode)
{
	cv::Size szAf = matP.size();
	if (szAf.width != 3 || szAf.height != 3)
		return -1;

	cv::Size sz0 = matBase.size();
	cv::Size sz1 = matOver.size();
	//std::cout << sz0 << std::endl;
	//std::cout << sz1 << std::endl;

	cv::Mat matP_inv;
	{
		double vp[4][2] = {
			0,0,
			sz0.width - 1, 0,
			sz0.width - 1, sz0.height - 1,
			0,sz0.height - 1
		};
		std::vector<cv::Point2f> pts1, pts2;
		for (int k = 0; k < 4; k++) {
			double x = matP.at<double>(0, 0) * vp[k][0] + matP.at<double>(0, 1) * vp[k][1] + matP.at<double>(0, 2);
			double y = matP.at<double>(1, 0) * vp[k][0] + matP.at<double>(1, 1) * vp[k][1] + matP.at<double>(1, 2);
			double z = matP.at<double>(2, 0) * vp[k][0] + matP.at<double>(2, 1) * vp[k][1] + matP.at<double>(2, 2);

			pts1.push_back(cv::Point2f(vp[k][0], vp[k][1]));
			pts2.push_back(cv::Point2f(x / z, y / z));
		}
		matP_inv = cv::getPerspectiveTransform(pts2, pts1);
	}

	int rangex[2] = { sz0.width - 1, 0 };
	int rangey[2] = { sz0.height - 1, 0 };
	double vp1[4][2] = {
		0, 0,
		sz1.width - 1, 0,
		sz1.width - 1, sz1.height - 1,
		0, sz1.height - 1
	};

	cv::Point vp0[4] = {
		cv::Point(0, 0),
		cv::Point(sz0.width - 1, 0),
		cv::Point(sz0.width - 1, sz0.height - 1),
		cv::Point(0, sz0.height - 1)
	};
	cv::Point vp1_inv[4];
	cv::Size sz_inv(sz1.width * 2, sz1.height * 2);

	for (int k = 0; k < 4; k++) {
		double x1 = matP_inv.at<double>(0, 0) * vp1[k][0] + matP_inv.at<double>(0, 1) * vp1[k][1] + matP_inv.at<double>(0, 2);
		double y1 = matP_inv.at<double>(1, 0) * vp1[k][0] + matP_inv.at<double>(1, 1) * vp1[k][1] + matP_inv.at<double>(1, 2);
		double z1 = matP_inv.at<double>(2, 0) * vp1[k][0] + matP_inv.at<double>(2, 1) * vp1[k][1] + matP_inv.at<double>(2, 2);

		int x = x1 / z1;
		int y = y1 / z1;
		vp1_inv[k] = cv::Point(x, y);

		if (x < -sz1.width) { x = -sz1.width; }
		if (y < -sz1.height) { y = -sz1.height; }
		if (x > sz_inv.width) { x = sz_inv.width; }
		if (y > sz_inv.height) { y = sz_inv.height; }

		if (x < rangex[0]) { rangex[0] = x; }
		if (rangex[1] < x) { rangex[1] = x; }
		if (y < rangey[0]) { rangey[0] = y; }
		if (rangey[1] < y) { rangey[1] = y; }

	}
	int margin[4] = { 0,0,0,0 };
	if (rangex[0] < 0) { margin[0] = -rangex[0]; }
	if (rangey[0] < 0) { margin[1] = -rangey[0]; }
	if (sz0.width <= rangex[1]) { margin[2] = rangex[1] - sz0.width + 1; }
	if (sz0.height <= rangey[1]) { margin[3] = rangey[1] - sz0.height + 1; }

	cv::Size sz0ex(sz0.width + margin[0] + margin[2], sz0.height + margin[1] + margin[3]);
	matOut = cv::Mat(sz0ex, CV_8UC3, cv::Scalar(0, 0, 0));

	if (mode == 0) {
		matBase.copyTo(matOut(cv::Rect(cv::Point(margin[0], margin[1]), sz0)));
	}

	for (int j = rangey[0]; j <= rangey[1]; j++) {
		for (int i = rangex[0]; i <= rangex[1]; i++) {
			int ii = i + margin[0];
			int jj = j + margin[1];
			//int x = matA.at<double>(0, 0)*i + matA.at<double>(0, 1)*j + matA.at<double>(0, 2);
			//int y = matA.at<double>(1, 0)*i + matA.at<double>(1, 1)*j + matA.at<double>(1, 2);
			double x1 = matP.at<double>(0, 0) * i + matP.at<double>(0, 1) * j + matP.at<double>(0, 2);
			double y1 = matP.at<double>(1, 0) * i + matP.at<double>(1, 1) * j + matP.at<double>(1, 2);
			double z1 = matP.at<double>(2, 0) * i + matP.at<double>(2, 1) * j + matP.at<double>(2, 2);

			int x = x1 / z1;
			int y = y1 / z1;

			if (x < 0 || sz1.width <= x || y < 0 || sz1.height <= y)
				continue;

			matOut.at<cv::Vec3b>(jj, ii) = matOver.at<cv::Vec3b>(y, x);
		}
	}
	if (mode != 0) {
		matBase.copyTo(matOut(cv::Rect(cv::Point(margin[0], margin[1]), sz0)));
	}

	if (mode == 0) {
		for (int k = 0; k < 4; k++) {
			int k2 = (k + 1) % 4;
			//cv::line(matOut, vp0[k], vp0[k2], cv::Scalar(0, 0, 255), 3);

			cv::Point p1(vp1_inv[k].x + margin[0], vp1_inv[k].y + margin[1]);
			cv::Point p2(vp1_inv[k2].x + margin[0], vp1_inv[k2].y + margin[1]);
			cv::line(matOut, p1, p2, cv::Scalar(0, 0, 255), 3);
		}
	}
	else {
		for (int k = 0; k < 4; k++) {
			int k2 = (k + 1) % 4;
			cv::Point p1(vp0[k].x + margin[0], vp0[k].y + margin[1]);
			cv::Point p2(vp0[k2].x + margin[0], vp0[k2].y + margin[1]);
			cv::line(matOut, p1, p2, cv::Scalar(0, 0, 255), 3);
		}
	}

	return 0;
}
