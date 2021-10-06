#include "kb_cv_perspective_transform.h"
#include "kb_cv_matmul_3x3.h"

//	ìäâeïœä∑çsóÒÇÃãtçsóÒÇåvéZÇ∑ÇÈ
int kb::inversePerspectiveTransform(cv::Mat& matP, cv::Size& sz1, cv::Mat& matP_inv, cv::Point2f pt_range[2])
{
	cv::Size szP = matP.size();
	if (szP.width < 3 || szP.height < 3)
		return -1;
	if (sz1.width < 3 || sz1.height < 3)
		return -1;

	double vp[5][2] = {
		0, 0,
		sz1.width - 1, 0,
		0, sz1.height - 1,
		sz1.width - 1, sz1.height - 1,
		(double)(sz1.width - 1) * 0.5, (double)(sz1.height - 1) * 0.5
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

	pt_range[0] = pts2[0];
	pt_range[1] = pts2[0];
	for (int k = 1; k < 4; k++) {
		if (pts2[k].x < pt_range[0].x) { pt_range[0].x = pts2[k].x; }
		if (pts2[k].y < pt_range[0].y) { pt_range[0].y = pts2[k].y; }
		if (pts2[k].x > pt_range[1].x) { pt_range[1].x = pts2[k].x; }
		if (pts2[k].y > pt_range[1].y) { pt_range[1].y = pts2[k].y; }
	}

	return 0;
}

int kb::updateRangePerspectiveTransform(
	std::vector<cv::Mat>& v_P,
	cv::Size& sz0,
	double rangex_out[2],
	double rangey_out[2]
)
{
	int num_P = v_P.size();
	double rangex_min[2] = { 0, sz0.width - 1 };
	double rangey_min[2] = { 0, sz0.height - 1 };

	for (int k = 0; k < num_P; k++) {
		cv::Size szAf = v_P[k].size();
		if (szAf.width == 0)
			continue;

		kb::updateRangePerspectiveTransform(v_P[k], sz0, rangex_min, rangey_min);
	}

	rangex_out[0] = rangex_min[0];
	rangex_out[1] = rangex_min[1];
	rangey_out[0] = rangey_min[0];
	rangey_out[1] = rangey_min[1];

	return 0;
}

//	


int kb::updateRangePerspectiveTransform(
	cv::Mat& matP, cv::Size& sz0,
	double rangex[2], double rangey[2])
{
	cv::Size szP = matP.size();
	if (szP.width < 3 || szP.height < 3)
		return -1;

	double vp[4][2] = {
		0,0,
		sz0.width - 1, 0,
		sz0.width - 1, sz0.height - 1,
		0,sz0.height - 1
	};
	for (int k = 0; k < 4; k++) {
		double x = matP.at<double>(0, 0) * vp[k][0] + matP.at<double>(0, 1) * vp[k][1] + matP.at<double>(0, 2);
		double y = matP.at<double>(1, 0) * vp[k][0] + matP.at<double>(1, 1) * vp[k][1] + matP.at<double>(1, 2);
		double z = matP.at<double>(2, 0) * vp[k][0] + matP.at<double>(2, 1) * vp[k][1] + matP.at<double>(2, 2);

		double xx = x / z;
		double yy = y / z;

		if (xx < rangex[0]) {
			rangex[0] = xx;
		}
		if (rangex[1] < xx) {
			rangex[1] = xx;
		}
		if (yy < rangey[0]) {
			rangey[0] = yy;
		}
		if (rangey[1] < yy) {
			rangey[1] = yy;
		}
	}
	return 0;
}

int kb::calcPerspectiveTransform(
	cv::Point2f& pt,
	std::vector<cv::Mat>& v_P1,
	std::vector<cv::Point2f>& v_pt_out
)
{
	int num = v_P1.size();
	v_pt_out.clear();
	v_pt_out.resize(num);

	for (int i = 0; i < num; i++) {
		cv::Mat matP = v_P1[i];
		cv::Size szP = v_P1[i].size();
		if (szP.width == 0)
			continue;

		double x = matP.at<double>(0, 0) * pt.x + matP.at<double>(0, 1) * pt.y + matP.at<double>(0, 2);
		double y = matP.at<double>(1, 0) * pt.x + matP.at<double>(1, 1) * pt.y + matP.at<double>(1, 2);
		double z = matP.at<double>(2, 0) * pt.x + matP.at<double>(2, 1) * pt.y + matP.at<double>(2, 2);

		v_pt_out[i] = cv::Point2f(x / z, y / z);
	}


	return 0;
}

int kb::forward_P(
	cv::Mat& matP_bf,
	cv::Mat& matP_in,
	cv::Mat& matP_out,
	cv::Size& sz0
)
{
	cv::Mat matP1 = matP_in;

	//std::cout << matP_bf << std::endl;
	//std::cout << matP_in << std::endl;


	cv::Size szAf = matP1.size();
	if (szAf.width != 3 || szAf.height != 3)
		return -1;

	cv::Mat matP_inv;
	cv::Point2f pt_range[2];
	if (kb::inversePerspectiveTransform(matP1, sz0, matP_inv, pt_range) < 0)
		return -1;

	cv::Mat matPP_inv = matP_bf * matP_inv;
	double a = matPP_inv.at<double>(2, 2);
	for (int j = 0; j < 3; j++) {
		for (int i = 0; i < 3; i++) {
			matPP_inv.at<double>(j, i) = matPP_inv.at<double>(j, i) / a;
		}
	}

	//std::cout << "aaa" << std::endl;
	{
		cv::Point2f pp1(sz0.width / 2, sz0.height / 2), pp2;
		kb::homogeneous_transformation_3x3(matPP_inv, pp1, pp2);

		cv::Point2f pp1a(0, 0), pp2a;
		kb::homogeneous_transformation_3x3(matPP_inv, pp1a, pp2a);
		cv::Point2f pp1b(sz0.width, 0), pp2b;
		kb::homogeneous_transformation_3x3(matPP_inv, pp1b, pp2b);
		cv::Point2f pp1c(0, sz0.height), pp2c;
		kb::homogeneous_transformation_3x3(matPP_inv, pp1c, pp2c);

		cv::Point2f dp1 = pp2b - pp2a;
		cv::Point2f dp2 = pp2c - pp2a;
		double cp = dp1.x * dp2.y - dp1.y * dp2.x;
		double cos1 = matPP_inv.at<double>(0, 0);
		double cos2 = matPP_inv.at<double>(1, 1);

		//std::cout << pp2 << ", "<<cp<<std::endl;

		if (cp > 0.0 && cos1 > 0.0 && cos2 > 0.0) {
		}
		else {
			std::cout << "error: kb::forward_P()" << std::endl;
			std::cout << matPP_inv << std::endl;
			//return -1;
		}
	}
	matPP_inv.copyTo(matP_out);

	return 0;
}


