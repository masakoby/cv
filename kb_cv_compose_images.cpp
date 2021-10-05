#include "kb_cv_compose_images.h"
#include "kb_cv_perspective_transform.h"
#include "kb_cv_matmul_3x3.h"

//	投影変換行列リストを使った順方向参照による画像合成
int kb::compose_images_forward(
	std::vector<cv::Mat>& v_images,
	std::vector<cv::Mat>& v_af,
	double rangex[2], double rangey[2],
	cv::Mat& matV
)
{
	int num_img = v_images.size();
	int num_af = v_af.size();
	if (num_img != num_af)
		return -1;

	cv::Size sz1(
		rangex[1] - rangex[0],
		rangey[1] - rangey[0]
	);
	if (sz1.width <= 0 || sz1.height <= 0)
		return -1;

	cv::Mat matF_r(sz1, CV_32F, cv::Scalar(0.0));
	cv::Mat matF_g(sz1, CV_32F, cv::Scalar(0.0));
	cv::Mat matF_b(sz1, CV_32F, cv::Scalar(0.0));
	cv::Mat matF_N(sz1, CV_32F, cv::Scalar(0.0));

	for (int k = 0; k < num_af; k++) {
		cv::Mat matP = v_af[k];
		cv::Size sz0 = v_images[k].size();

		//std::cout << matP << std::endl;
		for (int j = 0; j < sz0.height; j++) {
			for (int i = 0; i < sz0.width; i++) {
				double p[2] = { i,j };
				double x = matP.at<double>(0, 0) * p[0] + matP.at<double>(0, 1) * p[1] + matP.at<double>(0, 2);
				double y = matP.at<double>(1, 0) * p[0] + matP.at<double>(1, 1) * p[1] + matP.at<double>(1, 2);
				double z = matP.at<double>(2, 0) * p[0] + matP.at<double>(2, 1) * p[1] + matP.at<double>(2, 2);

				int i2 = (int)(x / z - rangex[0]);
				int j2 = (int)(y / z - rangey[0]);
				if (i2 < 0 || j2 < 0 || sz1.width <= i2 || sz1.height <= j2)
					continue;

				cv::Vec3b a = v_images[k].at<cv::Vec3b>(j, i);

				matF_r.at<float>(j2, i2) += (float)a[0];
				matF_g.at<float>(j2, i2) += (float)a[1];
				matF_b.at<float>(j2, i2) += (float)a[2];
				matF_N.at<float>(j2, i2) += 1.0;
			}
		}
	}

	matV = cv::Mat(sz1, CV_8UC3, cv::Scalar(0, 0, 0));

	for (int j = 0; j < sz1.height; j++) {
		for (int i = 0; i < sz1.width; i++) {
			if (matF_N.at<float>(j, i) < 0.5)
				continue;
			int a0 = matF_r.at<float>(j, i) / matF_N.at<float>(j, i);
			int a1 = matF_g.at<float>(j, i) / matF_N.at<float>(j, i);
			int a2 = matF_b.at<float>(j, i) / matF_N.at<float>(j, i);

			matV.at<cv::Vec3b>(j, i) = cv::Vec3b(a0, a1, a2);
		}
	}

	return 0;
}


int kb::compose_images_backward(
	std::vector<cv::Mat>& v_images,
	std::vector<cv::Mat>& v_af,
	double rangex[2], double rangey[2],
	cv::Mat& matV
)
{
	std::cout << "kb::compose_images_backward() " << std::endl;
	int num_img = v_images.size();
	int num_af = v_af.size();
	if (num_img < num_af || num_img <= 1)
		return -1;

	cv::Size sz1(
		rangex[1] - rangex[0],
		rangey[1] - rangey[0]
	);
	if (sz1.width <= 0 || sz1.height <= 0)
		return -1;

	//	
	std::vector<cv::Mat> v_af_inv;
	std::vector<cv::Point2f> v_range;
	{
		v_af_inv.resize(num_af);
		v_range.resize(num_af * 2);

		cv::Size sz_img = v_images[0].size();

		for (int k = 0; k < num_af; k++) {
			cv::Size sz_af = v_af[k].size();
			if (sz_af.width < 3 || sz_af.height < 3)
				continue;
			cv::Mat matP_inv;
			cv::Point2f range[2];
			if (kb::inversePerspectiveTransform(v_af[k], sz_img, matP_inv, range) < 0)
				continue;

			if (range[0].x < rangex[0]) {
				range[0].x = rangex[0];
			}
			if (range[0].y < rangey[0]) {
				range[0].y = rangey[0];
			}
			if (range[1].x > rangex[1]) {
				range[1].x = rangex[1];
			}
			if (range[1].y > rangey[1]) {
				range[1].y = rangey[1];
			}


			v_af_inv[k] = matP_inv;
			v_range[k * 2 + 0] = range[0];
			v_range[k * 2 + 1] = range[1];
		}
	}



	cv::Mat matF_r(sz1, CV_32F, cv::Scalar(0.0));
	cv::Mat matF_g(sz1, CV_32F, cv::Scalar(0.0));
	cv::Mat matF_b(sz1, CV_32F, cv::Scalar(0.0));
	cv::Mat matF_N(sz1, CV_32F, cv::Scalar(0.0));

	for (int k = 0; k < num_af; k++) {
		if ((k % 5) == 0) {
			std::cout << k << "/" << num_af << std::endl;
		}

		cv::Mat matP = v_af_inv[k];
		cv::Size sz_af = matP.size();
		if (sz_af.width < 3 || sz_af.height < 3)
			continue;

		cv::Size sz0 = v_images[k].size();

		cv::Point p_min = v_range[k * 2 + 0];
		cv::Point p_max = v_range[k * 2 + 1];

		for (int j2 = p_min.y; j2 <= p_max.y; j2++) {
			for (int i2 = p_min.x; i2 <= p_max.x; i2++) {
				int ii2 = i2 - rangex[0];
				int jj2 = j2 - rangey[0];
				if (ii2 < 0 || jj2 < 0 || sz1.width <= ii2 || sz1.height <= jj2)
					continue;

				double p[2] = { i2,j2 };
				double x = matP.at<double>(0, 0) * p[0] + matP.at<double>(0, 1) * p[1] + matP.at<double>(0, 2);
				double y = matP.at<double>(1, 0) * p[0] + matP.at<double>(1, 1) * p[1] + matP.at<double>(1, 2);
				double z = matP.at<double>(2, 0) * p[0] + matP.at<double>(2, 1) * p[1] + matP.at<double>(2, 2);


				int i1 = (int)(x / z);
				int j1 = (int)(y / z);

				if (i1 < 0 || j1 < 0 || sz0.width <= i1 || sz0.height <= j1)
					continue;

				cv::Vec3b a = v_images[k].at<cv::Vec3b>(j1, i1);

				matF_r.at<float>(jj2, ii2) += (float)a[0];
				matF_g.at<float>(jj2, ii2) += (float)a[1];
				matF_b.at<float>(jj2, ii2) += (float)a[2];
				matF_N.at<float>(jj2, ii2) += 1.0;
			}
		}
	}

	matV = cv::Mat(sz1, CV_8UC3, cv::Scalar(0, 0, 0));

	for (int j = 0; j < sz1.height; j++) {
		for (int i = 0; i < sz1.width; i++) {
			if (matF_N.at<float>(j, i) < 0.5)
				continue;
			int a0 = matF_r.at<float>(j, i) / matF_N.at<float>(j, i);
			int a1 = matF_g.at<float>(j, i) / matF_N.at<float>(j, i);
			int a2 = matF_b.at<float>(j, i) / matF_N.at<float>(j, i);

			matV.at<cv::Vec3b>(j, i) = cv::Vec3b(a0, a1, a2);
		}
	}

	return 0;
}

int kb::compose_images_backward_v2(
	std::vector<cv::Mat>& v_images,
	std::vector<cv::Mat>& v_af,
	double rangex[2], double rangey[2],
	cv::Mat& matV,
	double ratio_sigma = 1.0
)
{
	//std::cout << "kb::compose_images_backward() " << std::endl;
	int num_img = v_images.size();
	int num_af = v_af.size();
	if (num_img < num_af || num_img <= 1)
		return -1;

	cv::Size sz1(
		rangex[1] - rangex[0],
		rangey[1] - rangey[0]
	);
	if (sz1.width <= 0 || sz1.height <= 0)
		return -1;


	cv::Mat matW;

	//	
	std::vector<cv::Mat> v_af_inv;
	std::vector<cv::Point2f> v_range;
	{
		v_af_inv.resize(num_af);
		v_range.resize(num_af * 2);

		cv::Size sz_img = v_images[0].size();
		cv::Point p0(sz_img.width / 2, sz_img.height / 2);
		matW = cv::Mat(sz_img, CV_64F, cv::Scalar(0.0));

		double wt0 = 0.5 * (sz_img.width * sz_img.height) * ratio_sigma;

		for (int j = 0; j < sz_img.height; j++) {
			for (int i = 0; i < sz_img.width; i++) {
				double dx = i - p0.x;
				double dy = j - p0.y;
				double ds2 = -(dx * dx + dy * dy) / wt0;

				matW.at<double>(j, i) = exp(ds2);
			}
		}

		for (int k = 0; k < num_af; k++) {
			cv::Size sz_af = v_af[k].size();
			if (sz_af.width < 3 || sz_af.height < 3)
				continue;
			cv::Mat matP_inv;
			cv::Point2f range[2];
			if (kb::inversePerspectiveTransform(v_af[k], sz_img, matP_inv, range) < 0)
				continue;

			if (range[0].x < rangex[0]) {
				range[0].x = rangex[0];
			}
			if (range[0].y < rangey[0]) {
				range[0].y = rangey[0];
			}
			if (range[1].x > rangex[1]) {
				range[1].x = rangex[1];
			}
			if (range[1].y > rangey[1]) {
				range[1].y = rangey[1];
			}


			v_af_inv[k] = matP_inv;
			v_range[k * 2 + 0] = range[0];
			v_range[k * 2 + 1] = range[1];
		}
	}



	cv::Mat matF_r(sz1, CV_32F, cv::Scalar(0.0));
	cv::Mat matF_g(sz1, CV_32F, cv::Scalar(0.0));
	cv::Mat matF_b(sz1, CV_32F, cv::Scalar(0.0));
	cv::Mat matF_N(sz1, CV_64F, cv::Scalar(0.0));

	for (int k = 0; k < num_af; k++) {
		if ((k % 5) == 0) {
			//std::cout << k << "/" << num_af << std::endl;
		}

		cv::Mat matP = v_af_inv[k];
		cv::Size sz_af = matP.size();
		if (sz_af.width < 3 || sz_af.height < 3)
			continue;

		cv::Size sz0 = v_images[k].size();

		cv::Point p_min = v_range[k * 2 + 0];
		cv::Point p_max = v_range[k * 2 + 1];

		for (int j2 = p_min.y; j2 <= p_max.y; j2++) {
			for (int i2 = p_min.x; i2 <= p_max.x; i2++) {
				int ii2 = i2 - rangex[0];
				int jj2 = j2 - rangey[0];
				if (ii2 < 0 || jj2 < 0 || sz1.width <= ii2 || sz1.height <= jj2)
					continue;

				double p[2] = { i2,j2 };
				double x = matP.at<double>(0, 0) * p[0] + matP.at<double>(0, 1) * p[1] + matP.at<double>(0, 2);
				double y = matP.at<double>(1, 0) * p[0] + matP.at<double>(1, 1) * p[1] + matP.at<double>(1, 2);
				double z = matP.at<double>(2, 0) * p[0] + matP.at<double>(2, 1) * p[1] + matP.at<double>(2, 2);


				int i1 = (int)(x / z);
				int j1 = (int)(y / z);

				if (i1 < 0 || j1 < 0 || sz0.width <= i1 || sz0.height <= j1)
					continue;

				cv::Vec3b a = v_images[k].at<cv::Vec3b>(j1, i1);

				matF_r.at<float>(jj2, ii2) += (double)a[0] * matW.at<double>(j1, i1);
				matF_g.at<float>(jj2, ii2) += (double)a[1] * matW.at<double>(j1, i1);
				matF_b.at<float>(jj2, ii2) += (double)a[2] * matW.at<double>(j1, i1);
				matF_N.at<double>(jj2, ii2) += matW.at<double>(j1, i1);
			}
		}
	}

	matV = cv::Mat(sz1, CV_8UC3, cv::Scalar(0, 0, 0));

	for (int j = 0; j < sz1.height; j++) {
		for (int i = 0; i < sz1.width; i++) {
			if (matF_N.at<double>(j, i) < 0.00001)
				continue;
			int a0 = matF_r.at<float>(j, i) / matF_N.at<double>(j, i);
			int a1 = matF_g.at<float>(j, i) / matF_N.at<double>(j, i);
			int a2 = matF_b.at<float>(j, i) / matF_N.at<double>(j, i);
			if (a0 > 255) { a0 = 255; }
			if (a1 > 255) { a1 = 255; }
			if (a2 > 255) { a2 = 255; }

			matV.at<cv::Vec3b>(j, i) = cv::Vec3b(a0, a1, a2);
		}
	}

	return 0;
}


int kb::update_link(
	cv::Size& sz0,
	std::vector<cv::Mat>& v_P1,
	double rangex1[2], double rangey1[2],
	std::vector<int>& v_link,
	std::vector<cv::Point2f>& v_pt_out
)
{
	int num = v_P1.size();
	std::vector<cv::Point2f> v_pt[5];

	double p[5][3] = {
		sz0.width / 2, sz0.height / 2, 1.0,
		0,0,1.0,
		sz0.width, 0.0, 1.0,
		0.0, sz0.height, 1.0,
		sz0.width, sz0.height, 1.0
	};

	for (int j = 0; j < 5; j++) {
		v_pt[j].resize(num);
	}
	std::vector<int> v_state;
	v_state.resize(num, 1);
	for (int i = 0; i < num; i++) {
		cv::Mat matP = v_P1[i];
		cv::Size szP = v_P1[i].size();
		if (szP.width == 0) {
			v_state[i] = 0;
			continue;
		}

		for (int j = 0; j < 5; j++) {
			double x = matP.at<double>(0, 0) * p[j][0] + matP.at<double>(0, 1) * p[j][1] + matP.at<double>(0, 2);
			double y = matP.at<double>(1, 0) * p[j][0] + matP.at<double>(1, 1) * p[j][1] + matP.at<double>(1, 2);
			double z = matP.at<double>(2, 0) * p[j][0] + matP.at<double>(2, 1) * p[j][1] + matP.at<double>(2, 2);

			v_pt[j][i] = cv::Point2f(x / z, y / z);
		}
	}

	std::vector<double> v_len;
	v_len.resize(num, 0.0);
	for (int i = 0; i < num; i++) {
		if (v_state[i] == 0)
			continue;

		//中心から頂点までの距離を計算
		cv::Point2f v_sz[4] = {
			v_pt[1][i] - v_pt[0][i],
			v_pt[2][i] - v_pt[0][i],
			v_pt[3][i] - v_pt[0][i],
			v_pt[4][i] - v_pt[0][i]
		};

		//
		double min_len = 0;
		double len[4];
		for (int ii = 0; ii < 4; ii++) {
			len[ii] = sqrt(v_sz[ii].x * v_sz[ii].x + v_sz[ii].y * v_sz[ii].y);

			if (ii == 0 || len[ii] > min_len) {
				min_len = len[ii];
			}
		}

		v_len[i] = min_len;
	}

	//	最大上位２つまでリンクを追加
	for (int i1 = 2; i1 < num - 1; i1++) {
		if (v_state[i1] == 0 || v_state[i1 + 1] == 0)
			continue;

		cv::Point2f dir12 = v_pt[0][i1 + 1] - v_pt[0][i1];
		double len_dir12 = sqrt(dir12.x * dir12.x + dir12.y * dir12.y);

		//double dp_min[2] = { 1,1 };
		double dp_min[2] = { -1,-1 };
		int idx[2] = { -1,-1 };
		for (int i2 = 0; i2 < i1 - 1; i2++) {
			if (v_state[i2] == 0)
				continue;

			double thres0 = (v_len[i1] + v_len[i2]) * 0.5;
			double thres1 = thres0 * 0.2;
			double thres2 = thres0 * 1.5;

			cv::Point2f p12 = v_pt[0][i2] - v_pt[0][i1];
			double len12 = sqrt(p12.x * p12.x + p12.y * p12.y);

			double dp = (dir12.x * p12.x + dir12.y * p12.y) / (len_dir12 * len12);
			double cp = (dir12.x * p12.y - dir12.y * p12.x) / (len_dir12 * len12);
			if (dp < 0.0) { dp = -dp; }

			if (thres1 < len12 && len12 < thres2) {
				if (cp > 0.5) {
					if (dp_min[0] < 0.0 || len12 < dp_min[0]) {
						dp_min[0] = len12;
						idx[0] = i2;
					}
					//if ((dp_min[0]) > dp) {
					//	dp_min[0] = dp;
					//	idx[0] = i2;
					//}
				}
				else if (cp < -0.5) {
					if (dp_min[1] < 0.0 || len12 < dp_min[1]) {
						dp_min[1] = len12;
						idx[1] = i2;
					}
					//if ((dp_min[1]) > dp) {
					//	dp_min[1] = dp;
					//	idx[1] = i2;
					//}
				}

			}
		}

		if (idx[0] >= 0) {
			v_link.push_back(idx[0]);
			v_link.push_back(i1);
		}
		if (idx[1] >= 0) {
			v_link.push_back(idx[1]);
			v_link.push_back(i1);
		}
	}

	//
	v_pt_out = v_pt[0];

	return 0;
}

int kb::update_link0(
	cv::Size& sz0,
	std::vector<cv::Mat>& v_P1,
	std::vector<cv::Point2f>& v_pt_out
)
{
	int num = v_P1.size();
	std::vector<cv::Point2f> v_pt[5];

	double p[5][3] = {
		sz0.width / 2, sz0.height / 2, 1.0,
		0,0,1.0,
		sz0.width, 0.0, 1.0,
		0.0, sz0.height, 1.0,
		sz0.width, sz0.height, 1.0
	};

	for (int j = 0; j < 5; j++) {
		v_pt[j].resize(num);
	}
	std::vector<int> v_state;
	v_state.resize(num, 1);
	for (int i = 0; i < num; i++) {
		cv::Mat matP = v_P1[i];
		cv::Size szP = v_P1[i].size();
		if (szP.width == 0) {
			v_state[i] = 0;
			continue;
		}

		for (int j = 0; j < 5; j++) {
			double x = matP.at<double>(0, 0) * p[j][0] + matP.at<double>(0, 1) * p[j][1] + matP.at<double>(0, 2);
			double y = matP.at<double>(1, 0) * p[j][0] + matP.at<double>(1, 1) * p[j][1] + matP.at<double>(1, 2);
			double z = matP.at<double>(2, 0) * p[j][0] + matP.at<double>(2, 1) * p[j][1] + matP.at<double>(2, 2);

			v_pt[j][i] = cv::Point2f(x / z, y / z);
		}
	}

	//
	v_pt_out = v_pt[0];

	return 0;
}


int kb::draw_trackingline(
	cv::Mat& matV,
	cv::Size& sz0,
	std::vector<cv::Mat>& v_P1,
	double rangex1[2], double rangey1[2]
)
{
	cv::Size sz1 = matV.size();

	int num = v_P1.size();
	std::vector<cv::Point2f> v_pt;

	double p[3] = { sz0.width / 2, sz0.height / 2, 1.0 };
	for (int i = 0; i < num; i++) {
		cv::Mat matP = v_P1[i];

		double x = matP.at<double>(0, 0) * p[0] + matP.at<double>(0, 1) * p[1] + matP.at<double>(0, 2);
		double y = matP.at<double>(1, 0) * p[0] + matP.at<double>(1, 1) * p[1] + matP.at<double>(1, 2);
		double z = matP.at<double>(2, 0) * p[0] + matP.at<double>(2, 1) * p[1] + matP.at<double>(2, 2);

		v_pt.push_back(cv::Point2f(x / z - rangex1[0], y / z - rangey1[0]));
	}

	for (int i = 0; i < num - 1; i++) {
		cv::line(matV, v_pt[i], v_pt[i + 1], cv::Scalar(0, 255, 0), 3);
	}
	for (int i = 0; i < num; i++) {
		cv::circle(matV, v_pt[i], 5, cv::Scalar(0, 0, 255), 3);
	}

}

int kb::draw_trackingline(
	cv::Mat& matV,
	std::vector<cv::Point2f>& v_pt,
	std::vector<int>& vflag,
	double rangex1[2], double rangey1[2],
	std::vector<int>& v_link,
	cv::Scalar color_line
)
{
	cv::Size sz1 = matV.size();

	int num = v_link.size() / 2;
	int num_pt = v_pt.size();
	int num_pt2 = vflag.size();
	if (num_pt2 != num_pt)
		return -1;

	for (int i = 0; i < num; i++) {
		int i1 = v_link[i * 2];
		int i2 = v_link[i * 2 + 1];
		if (i1 < 0 || i2 < 0 || num_pt <= i1 || num_pt <= i2)
			continue;
		if (vflag[i1] == 0 || vflag[i2] == 0)
			continue;
		cv::Point p1, p2;

		p1.x = v_pt[i1].x - rangex1[0];
		p1.y = v_pt[i1].y - rangey1[0];
		p2.x = v_pt[i2].x - rangex1[0];
		p2.y = v_pt[i2].y - rangey1[0];


		cv::line(matV, p1, p2, color_line, 3);
		//cv::line(matV, p1, p2, cv::Scalar(0, 255, 0), 3);
	}
	for (int i = 0; i < num_pt; i++) {
		if (vflag[i] == 0)
			continue;

		cv::Point p1;
		p1.x = v_pt[i].x - rangex1[0];
		p1.y = v_pt[i].y - rangey1[0];

		cv::circle(matV, p1, 5, cv::Scalar(0, 0, 255), 3);
	}

	return 0;
}

int kb::compose_matP(
	std::vector<cv::Mat>& v_Af,
	cv::Size& sz0,
	std::vector<cv::Mat>& v_P_out,
	double rangex_out[2],
	double rangey_out[2],
	cv::Mat matEye// = cv::Mat::eye(cv::Size(3, 3), CV_64F)
)
{
	if (sz0.width <= 0 || sz0.height <= 0) {
		std::cout << "error: kb::compose_matP(), " << sz0 << std::endl;
		return -1;
	}

	//
	//	v_P_neighborには、隣接間のアフィン変換行列が入っている。
	//	隣接情報に基づいて、張り合わせるには、隣接間のアフィン変換行列を
	//	貼り合わせ後の全体画像の中のアフィン変換行列に表現しなおさなければならない。
	//	

	//	連続した、処理可能な投影変換行列を抽出して、配列へ入れなおす。
	//	データがある場所までは処理する

	int num_af = v_Af.size();
	int num_mat = num_af + 1;

	//
	//	どの位置を起点にして、張り合わせると
	//	全体画像が一番小さくなるのかを計算する
	//
	int k0_min = -1;
	int sz_min = 0;

	v_P_out.resize(num_mat);
	double rangex_min[2] = { 0, sz0.width - 1 };
	double rangey_min[2] = { 0, sz0.height - 1 };

	int cnt_valid_max = 0;
	int range_idx[2] = { 0,num_af - 1 };

	for (int k0 = 0; k0 < num_af; k0++) {
		std::vector<cv::Mat> v_P;
		v_P.resize(num_mat);

		double rangex[2] = { 0, sz0.width - 1 };
		double rangey[2] = { 0, sz0.height - 1 };

		//std::cout << "--" << std::endl;

		int cnt_valid = 0;
		int idx_max = k0;
		int idx_min = k0;
		int state_inv1 = 0;
		int state_inv2 = 0;

		//	順方向
		{
			cv::Mat matPx_inv;// = matEye;// cv::Mat::eye(cv::Size(3, 3), CV_64F);
			matEye.copyTo(matPx_inv);
			matPx_inv.copyTo(v_P[k0]);

			for (int k = k0; k < num_af; k++) {
				cv::Mat matP1 = v_Af[k];

				cv::Size szAf = matP1.size();
				if (szAf.width != 3 || szAf.height != 3)
					break;

				cv::Mat matP_inv;
				cv::Point2f pt_range[2];
				if (kb::inversePerspectiveTransform(matP1, sz0, matP_inv, pt_range) < 0)
					break;

				cv::Mat matPP_inv = matPx_inv * matP_inv;
				double a = matPP_inv.at<double>(2, 2);
				for (int j = 0; j < 3; j++) {
					for (int i = 0; i < 3; i++) {
						matPP_inv.at<double>(j, i) = matPP_inv.at<double>(j, i) / a;
					}
				}


				matPP_inv.copyTo(matPx_inv);

				{
					cv::Point2f pp1(sz0.width / 2, sz0.height / 2), pp2;
					kb::homogeneous_transformation_3x3(matPx_inv, pp1, pp2);

					cv::Point2f pp1a(0, 0), pp2a;
					kb::homogeneous_transformation_3x3(matPx_inv, pp1a, pp2a);
					cv::Point2f pp1b(sz0.width, 0), pp2b;
					kb::homogeneous_transformation_3x3(matPx_inv, pp1b, pp2b);
					cv::Point2f pp1c(0, sz0.height), pp2c;
					kb::homogeneous_transformation_3x3(matPx_inv, pp1c, pp2c);

					cv::Point2f dp1 = pp2b - pp2a;
					cv::Point2f dp2 = pp2c - pp2a;
					double cp = dp1.x * dp2.y - dp1.y * dp2.x;
					double cos1 = matPx_inv.at<double>(0, 0);
					double cos2 = matPx_inv.at<double>(1, 1);

					//std::cout << pp2 << ", "<<cp<<std::endl;

					if (state_inv1 == 0) {
						if (cp > 0.0 && cos1 > 0.0 && cos2 > 0.0) {
							cnt_valid++;
						}
						else {
							state_inv1 = 1;
							idx_max = k;
							break;
						}
					}
				}
				matPx_inv.copyTo(v_P[k + 1]);

				if (state_inv1 == 0) {
					kb::updateRangePerspectiveTransform(matPx_inv, sz0, rangex, rangey);
				}
			}
		}

		//std::cout << "" << std::endl;

		//	逆方向
		{
			cv::Mat matPx;// = matEye;// cv::Mat::eye(cv::Size(3, 3), CV_64F);
			matEye.copyTo(matPx);
			for (int k = k0 - 1; k >= 0; k--) {
				cv::Mat matP1 = v_Af[k];

				cv::Size szAf = matP1.size();
				if (szAf.width != 3 || szAf.height != 3)
					break;

				cv::Mat matPP = matPx * matP1;
				double a = matPP.at<double>(2, 2);
				for (int j = 0; j < 3; j++) {
					for (int i = 0; i < 3; i++) {
						matPP.at<double>(j, i) = matPP.at<double>(j, i) / a;
					}
				}

				matPP.copyTo(matPx);

				{
					cv::Point2f pp1(sz0.width / 2, sz0.height / 2), pp2;
					kb::homogeneous_transformation_3x3(matPx, pp1, pp2);

					cv::Point2f pp1a(0, 0), pp2a;
					kb::homogeneous_transformation_3x3(matPx, pp1a, pp2a);
					cv::Point2f pp1b(sz0.width, 0), pp2b;
					kb::homogeneous_transformation_3x3(matPx, pp1b, pp2b);
					cv::Point2f pp1c(0, sz0.height), pp2c;
					kb::homogeneous_transformation_3x3(matPx, pp1c, pp2c);

					cv::Point2f dp1 = pp2b - pp2a;
					cv::Point2f dp2 = pp2c - pp2a;
					double cp = dp1.x * dp2.y - dp1.y * dp2.x;
					double cos1 = matPx.at<double>(0, 0);
					double cos2 = matPx.at<double>(1, 1);

					//std::cout << pp2 << ", " << cp << std::endl;

					if (state_inv2 == 0) {
						if (cp > 0.0 && cos1 > 0.0 && cos2 > 0.0) {
							cnt_valid++;
						}
						else {
							state_inv2 = 1;
							idx_min = k + 1;
							break;
						}
					}
				}

				if (state_inv2 == 0) {
					kb::updateRangePerspectiveTransform(matPx, sz0, rangex, rangey);
				}
				matPx.copyTo(v_P[k]);
			}
		}
		//getchar();

		//	更新条件
		int flag_update = 0;
		int s1 = 0;
		if (cnt_valid_max < cnt_valid) {
			cnt_valid_max = cnt_valid;

			cv::Size sz1(
				rangex[1] - rangex[0],
				rangey[1] - rangey[0]
			);

			s1 = sz1.width + sz1.height;
			flag_update = 1;
		}
		else if (cnt_valid_max == cnt_valid) {

			cv::Size sz1(
				rangex[1] - rangex[0],
				rangey[1] - rangey[0]
			);

			s1 = sz1.width + sz1.height;
			if (k0_min < 0 || s1 < sz_min) {
				flag_update = 1;
			}
		}

		//	更新処理
		if (flag_update == 1) {
			k0_min = k0;
			sz_min = s1;

			rangex_min[0] = rangex[0];
			rangex_min[1] = rangex[1];
			rangey_min[0] = rangey[0];
			rangey_min[1] = rangey[1];

			v_P_out.clear();
			v_P_out.resize(num_mat);

			for (int k = 0; k < num_mat; k++) {
				cv::Size szP = v_P[k].size();
				if (szP.width == 0)
					continue;
				v_P[k].copyTo(v_P_out[k]);
			}
		}

		std::cout << k0 << ": " << sz_min << ", valid count=" << cnt_valid << ", index range=[" << idx_min << ", " << idx_max << "]" << std::endl;

	}

	//	行列を正規化
	for (int k = 0; k < num_mat; k++) {
		cv::Size szP = v_P_out[k].size();
		if (szP.width == 0)
			continue;

		double a = v_P_out[k].at<double>(2, 2);
		for (int j = 0; j < 3; j++) {
			for (int i = 0; i < 3; i++) {
				v_P_out[k].at<double>(j, i) = v_P_out[k].at<double>(j, i) / a;
			}
		}
	}


	std::cout << "rangex: " << rangex_min[0] << ", " << rangex_min[1] << std::endl;
	std::cout << "rangey: " << rangey_min[0] << ", " << rangey_min[1] << std::endl;
	std::cout << sz0 << std::endl;
	//getchar();

	rangex_out[0] = rangex_min[0];
	rangex_out[1] = rangex_min[1];
	rangey_out[0] = rangey_min[0];
	rangey_out[1] = rangey_min[1];

	return 0;
}

