#define _USE_MATH_DEFINES
#include <math.h>

#include "kb_cv_uv2cube.h"


//int kb::CUv2Cube::create(cv::Size szUV, int cx)
//{
//
//
//	////	全体画像バッファ作成
//	//cv::Mat matRGB_ov[6];
//	//for (int k = 0; k < 6; k++) {
//	//	matRGB_ov[k] = cv::Mat(cx, cx, CV_8UC3, color_bk);
//	//}
//
//	double half_cx = (double)(cx - 1) * 0.5;
//
//	for (int k = 0; k < 6; k++) {
//		m_lut[k] = cv::Mat(cx, cx, CV_32SC2);
//	}
//
//	m_szUV = szUV;
//
//	cv::Vec2i bk(-1, -1);
//	{
//		for (int kk = 0; kk < 6; kk++) {
//			for (int y = 0; y < cx; y++) {
//				for (int x = 0; x < cx; x++) {
//					double p3[3] = { (double)x / half_cx - 1.0, (double)y / half_cx - 1.0, 1.0 };
//					double d = sqrt(p3[0] * p3[0] + p3[1] * p3[1] + p3[2] * p3[2]);
//					double up3[3] = { p3[0] / d, p3[1] / d, p3[2] / d };
//
//					double up3t[3];
//					kb::matmul_3x3_3x1(cube_matR[kk], up3, up3t);
//
//					double u = 0.5 - atan2(up3t[1], up3t[0]) / (2.0 * M_PI);
//					double v = 0.5 - asin(up3t[2]) / M_PI;
//
//					int ii = szUV.width * u;
//					int jj = szUV.height * v;
//
//					cv::Vec2i a;
//					if (ii < 0 || jj < 0 || szUV.width <= ii || szUV.height <= jj) {
//						a[0] = -1;
//						a[1] = -1;
//					}
//					else {
//						a[0] = ii;
//						a[1] = jj;
//					}
//					m_lut[kk].at<cv::Vec2i>(y, x) = a;
//				}
//			}
//		}
//	}
//	return 0;
//}

int kb::CUv2Cube::create(cv::Size szUV, int cx)
{
	double half_cx = (double)(cx - 1) * 0.5;

	for (int k = 0; k < 6; k++) {
		m_lut[k] = cv::Mat(cx, cx, CV_32SC2);
	}

	m_szUV = szUV;

	cv::Vec2i bk(-1, -1);
	{
		for (int kk = 0; kk < 6; kk++) {
			for (int y = 0; y < cx; y++) {
				for (int x = 0; x < cx; x++) {
					double p3[3] = { (double)x / half_cx - 1.0, (double)y / half_cx - 1.0, 1.0 };
					double d = sqrt(p3[0] * p3[0] + p3[1] * p3[1] + p3[2] * p3[2]);
					double up3[3] = { p3[0] / d, p3[1] / d, p3[2] / d };

					double up3t[3];
					kb::matmul_3x3_3x1(cube_matR[kk], up3, up3t);

					double u = 0.5 - atan2(up3t[1], up3t[0]) / (2.0 * M_PI);
					double v = 0.5 - asin(up3t[2]) / M_PI;

					int ii = szUV.width * u;
					int jj = szUV.height * v;

					cv::Vec2i a;
					if (ii < 0 || jj < 0 || szUV.width <= ii || szUV.height <= jj) {
						a[0] = -1;
						a[1] = -1;
					}
					else {
						a[0] = ii;
						a[1] = jj;
					}
					m_lut[kk].at<cv::Vec2i>(y, x) = a;
				}
			}
		}
	}

	m_lut_inv = cv::Mat(m_szUV, CV_32SC2, bk);
	m_lut_idx = cv::Mat(m_szUV, CV_32SC1, -1);
	cv::Mat matV(m_szUV, CV_8UC3);
	cv::Vec3b color[6] = {
		cv::Vec3b(0,0,0),
		cv::Vec3b(0,0,255),
		cv::Vec3b(0,255,0),
		cv::Vec3b(255,0,0),
		cv::Vec3b(128,128,128),
		cv::Vec3b(255,255,255)
	};

	{
		double dir_face[6][3];
		for (int k = 0; k < 6; k++) {
			double p[3] = { 0,0,1 };
			kb::matmul_3x3_3x1(cube_matR[k], p, dir_face[k]);
		}

		for (int j = 0; j < szUV.height; j++) {
			for (int i = 0; i < szUV.width; i++) {
				double u = (double)i / (double)szUV.width;
				double v = ((double)j+0.5) / (double)szUV.height;

				double x = cos((0.5 - u) * 2.0 * M_PI);
				double y = sin((0.5 - u) * 2.0 * M_PI);
				//double x = 1;
				//double y = tan((0.5 - u) * 2.0 * M_PI);
				double z = sin((0.5 - v) * M_PI);
				double z2 = cos((0.5 - v) * M_PI);
				double r = sqrt(z2 * z2);// / sqrt(x * x + y * y);
				x = x * r;
				y = y * r;

				int k_max = -1;
				double dp_max = -1;
				for (int k = 0; k < 6; k++) {
					double dp = dir_face[k][0] * x + dir_face[k][1] * y + dir_face[k][2] * z;
					if (dp_max < dp) {
						k_max = k;
						dp_max = dp;
					}
				}

				double up3t[3] = { x,y,z }, up3[3];
				kb::matmul_1x3_3x3(up3t, cube_matR[k_max], up3);
				if (up3[2] < 0.0)
					continue;

				int xx = (up3[0] / up3[2] + 1.0) * (double)half_cx;
				int yy = (up3[1] / up3[2] + 1.0) * (double)half_cx;

				if (xx < 0 || cx <= xx || yy < 0 || cx <= yy)
					continue;
				m_lut_inv.at<cv::Vec2i>(j, i) = cv::Vec2i(xx, yy);
				m_lut_idx.at<int>(j, i) = k_max;
				matV.at<cv::Vec3b>(j, i) = color[k_max];
			}
		}
	}
	//cv::namedWindow("cube", cv::WINDOW_NORMAL);
	//cv::imshow("cube", matV);
	//int rtn = cv::waitKeyEx(0);


	return 0;
}




int kb::CUv2Cube::run_lut(cv::Mat& matUV, cv::Mat& matCube, int idx)
{
	if (idx < 0 || 5 < idx)
		return -1;

	cv::Size szUV = matUV.size();
	cv::Size szCube = m_lut[idx].size();

	if (szUV != m_szUV)
		return -1;
	if (szCube.width <= 0 || szCube.height <= 0)
		return -1;

	int cx = szCube.width;

	cv::Scalar color_bk(0, 0, 0);
	matCube = cv::Mat(cx, cx, CV_8UC3, color_bk);

	for (int y = 0; y < cx; y++) {
		for (int x = 0; x < cx; x++) {
			cv::Vec2i a = m_lut[idx].at<cv::Vec2i>(y, x);
			if (a[0] < 0 || a[1] < 0)
				continue;

			matCube.at<cv::Vec3b>(y, x) = matUV.at<cv::Vec3b>(a[1], a[0]);
		}
	}

	return 0;
}


int kb::CUv2Cube::run_lut_inv(cv::Mat& matUV, cv::Mat& matCube, int idx, cv::Vec3b color_ov)
{
	if (idx < 0 || 5 < idx)
		return -1;

	cv::Size szUV = matUV.size();
	cv::Size szCube = matCube.size();
	cv::Scalar color_bk(0, 0, 0);

	if (szUV != m_szUV) {
		matUV = cv::Mat(m_szUV, CV_8UC3, color_bk);
	}
	if (szCube.width <= 0 || szCube.height <= 0)
		return -1;

	int cx = szCube.width;

	int cnt = 0;
	if (color_ov[0] == 0 && color_ov[1] == 0 && color_ov[2] == 0) {
		for (int y = 0; y < m_szUV.height; y++) {
			for (int x = 0; x < m_szUV.width; x++) {
				cv::Vec2i a = m_lut_inv.at<cv::Vec2i>(y, x);
				int k = m_lut_idx.at<int>(y, x);
				if (k != idx)
					continue;

				if (a[0] < 0 || a[1] < 0)
					continue;

				cv::Vec3b b = matCube.at<cv::Vec3b>(a[1], a[0]);
				if (b[0] == 0 && b[1] == 0 && b[2] == 0)
					continue;


				matUV.at<cv::Vec3b>(y, x) = b;
				cnt++;
			}
		}
	}
	else {
		for (int y = 0; y < m_szUV.height; y++) {
			for (int x = 0; x < m_szUV.width; x++) {
				cv::Vec2i a = m_lut_inv.at<cv::Vec2i>(y, x);
				int k = m_lut_idx.at<int>(y, x);
				if (k != idx)
					continue;

				if (a[0] < 0 || a[1] < 0)
					continue;

				cv::Vec3b b = matCube.at<cv::Vec3b>(a[1], a[0]);
				if (b[0] == 0 && b[1] == 0 && b[2] == 0)
					continue;


				matUV.at<cv::Vec3b>(y, x) = color_ov;
				cnt++;
			}
		}
	}
	std::cout<<cnt<<std::endl;

	return 0;
}
