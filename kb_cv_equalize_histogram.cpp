#include "kb_cv_equalize_histogram.h"

#include "kb_cv_histogram.h"
#include "kb_cv_cvtColor.h"

int kb::equalizeHistForRGB(
	cv::Mat& matRGB, cv::Mat& matRGB_out, float step, int flag_sm, double sigma,
	double sat_ratio)
{
	cv::Mat matL1;	kb::RGB2Lum_32F(matRGB, matL1);
	cv::Mat matL1g;
	if (flag_sm == 0) {
		matL1g = matL1;
	}
	else {
		if (sigma < 0.001) {
			sigma = 0.001;
		}
		cv::GaussianBlur(matL1, matL1g, cv::Size(3, 3), sigma);
	}
	cv::Mat matL2;	kb::equalizeHist_32F(matL1g, matL2, step);

	cv::Mat matHSV;	cv::cvtColor(matRGB, matHSV, cv::COLOR_BGR2HSV);
	cv::Size sz = matHSV.size();
	for (int j = 0; j < sz.height; j++) {
		for (int i = 0; i < sz.width; i++) {
			cv::Vec3b a = matHSV.at<cv::Vec3b>(j, i);
			int a2 = matL2.at<float>(j, i);
			int s2 = (int)((double)a[1] * sat_ratio);
			if (s2 > 255) { s2 = 255; }
			a[1] = s2;
			a[2] = a2;
			matHSV.at<cv::Vec3b>(j, i) = a;
		}
	}
	cv::cvtColor(matHSV, matRGB_out, cv::COLOR_HSV2BGR);

	return 0;
}


int kb::equalizeHistForRGB2(
	cv::Mat& matRGB,
	cv::Mat& matRGB_out,
	float step_hist,//=1.0, 
	double ratio_sigma,//=0.1, 
	int window_size,//=80, 
	int window_step,//=20,
	int num_thread,//=1
	int flag_sm,//=0
	double sigma,
	double sat_ratio
)
{
	cv::Size sz1 = matRGB.size();

	int w1 = window_size;
	int w2 = window_step;
	float step = step_hist;
	if (step < 0.01) { step = 0.01; }

	if (w1 < 10) { w1 = 10; }
	if (w2 < 1) { w2 = 1; }
	else if (w1 < w2) { w2 = w1; }

	int n1 = (sz1.width - w1) / w2 + 1;
	int n2 = (sz1.height - w1) / w2 + 1;

	cv::Mat matAll(sz1, CV_8UC3);
	cv::Mat matF_r(sz1, CV_64F, cv::Scalar(0)), matF_g(sz1, CV_64F, cv::Scalar(0)), matF_b(sz1, CV_64F, cv::Scalar(0));
	cv::Mat matF_cnt(sz1, CV_64F, cv::Scalar(0));

	//double ratio_sigma=0.1;

	cv::Mat matF_wt(cv::Size(w1, w1), CV_64F, cv::Scalar(0));
	{
		int xm = w1 / 2;
		double wt0 = 2.0 * (xm * xm) * ratio_sigma;
		for (int jj = 0; jj < w1; jj++) {
			for (int ii = 0; ii < w1; ii++) {
				matF_wt.at<double>(jj, ii) = exp(-(double)((ii - xm) * (ii - xm) + (jj - xm) * (jj - xm)) / wt0);
			}
		}
	}

	int step_add_x = 0;
	int step_add_y = 0;
	{

		int x1_max = (n1 - 1) * w2 + w1;
		int y1_max = (n2 - 1) * w2 + w1;

		//std::cout << sz1 << std::endl;
		//std::cout << x1_max<<", "<<y1_max << std::endl;

		int amari_x = sz1.width - x1_max;
		int amari_y = sz1.height - y1_max;

		if (amari_x > 0 && n1 >= 2) {
			step_add_x = amari_x / (n1 - 1);
			if ((amari_x % (n1 - 1)) > 0) {
				step_add_x++;
			}
		}
		if (amari_y > 0 && n2 >= 2) {
			step_add_y = amari_y / (n2 - 1);
			if ((amari_y % (n2 - 1)) > 0) {
				step_add_y++;
			}
		}
		//std::cout << step_add_x << ", " << step_add_y << std::endl;

	}
	if (num_thread <= 1) {
		for (int j = 0; j < n2; j++) {
			for (int i = 0; i < n1; i++) {
				int x0 = i * (w2 + step_add_x); int x1 = x0 + w1;
				int y0 = j * (w2 + step_add_y); int y1 = y0 + w1;

				if (x1 >= sz1.width) { x1 = sz1.width; x0 = x1 - w1; }
				if (y1 >= sz1.height) { y1 = sz1.height; y0 = y1 - w1; }

				cv::Rect rect(x0, y0, w1, w1);

				cv::Mat mat1;
				matRGB(rect).copyTo(mat1);

				cv::Mat mat1_out;
				kb::equalizeHistForRGB(mat1, mat1_out, step, flag_sm, sigma, sat_ratio);


				for (int jj = 0; jj < w1; jj++) {
					for (int ii = 0; ii < w1; ii++) {
						//double wt=  exp( -(double)( (ii-xm)*(ii-xm)+(jj-ym)*(jj-ym) )/wt0 );
						double wt = matF_wt.at<double>(jj, ii);

						cv::Vec3b a1 = mat1_out.at<cv::Vec3b>(jj, ii);

						matF_r.at<double>(y0 + jj, x0 + ii) += (double)a1[2] * wt;
						matF_g.at<double>(y0 + jj, x0 + ii) += (double)a1[1] * wt;
						matF_b.at<double>(y0 + jj, x0 + ii) += (double)a1[0] * wt;
						matF_cnt.at<double>(y0 + jj, x0 + ii) += wt;
					}
				}
			}
		}

	}
	else {
		std::vector<cv::Mat> vec_mat;
		vec_mat.resize(n1 * n2);

#pragma omp parallel num_threads(num_thread)
		{
#pragma omp for 
			for (int j = 0; j < n2; j++) {
				for (int i = 0; i < n1; i++) {
					int x0 = i * (w2 + step_add_x); int x1 = x0 + w1;
					int y0 = j * (w2 + step_add_y); int y1 = y0 + w1;
					//int x0 = i * w2; int x1 = x0 + w1;
					//int y0 = j * w2; int y1 = y0 + w1;

					if (x1 >= sz1.width) { x1 = sz1.width; x0 = x1 - w1; }
					if (y1 >= sz1.height) { y1 = sz1.height; y0 = y1 - w1; }

					cv::Rect rect(x0, y0, w1, w1);

					cv::Mat mat1;
					matRGB(rect).copyTo(mat1);

					cv::Mat mat1_out;
					kb::equalizeHistForRGB(mat1, mat1_out, step, flag_sm, sigma, sat_ratio);

					vec_mat[i + j * n1] = mat1_out;
				}
			}
		}

		for (int j = 0; j < n2; j++) {
			for (int i = 0; i < n1; i++) {
				//int x0 = i * w2; int x1 = x0 + w1;
				//int y0 = j * w2; int y1 = y0 + w1;
				int x0 = i * (w2 + step_add_x); int x1 = x0 + w1;
				int y0 = j * (w2 + step_add_y); int y1 = y0 + w1;

				if (x1 >= sz1.width) { x1 = sz1.width; x0 = x1 - w1; }
				if (y1 >= sz1.height) { y1 = sz1.height; y0 = y1 - w1; }

				for (int jj = 0; jj < w1; jj++) {
					for (int ii = 0; ii < w1; ii++) {
						double wt = matF_wt.at<double>(jj, ii);

						cv::Vec3b a1 = vec_mat[i + j * n1].at<cv::Vec3b>(jj, ii);

						matF_r.at<double>(y0 + jj, x0 + ii) += (double)a1[2] * wt;
						matF_g.at<double>(y0 + jj, x0 + ii) += (double)a1[1] * wt;
						matF_b.at<double>(y0 + jj, x0 + ii) += (double)a1[0] * wt;
						matF_cnt.at<double>(y0 + jj, x0 + ii) += wt;
					}
				}
			}
		}

	}

	for (int y = 0; y < sz1.height; y++) {
		for (int x = 0; x < sz1.width; x++) {
			if (matF_cnt.at<double>(y, x) < 0.0001)
				continue;
			int r = matF_r.at<double>(y, x) / matF_cnt.at<double>(y, x);
			int g = matF_g.at<double>(y, x) / matF_cnt.at<double>(y, x);
			int b = matF_b.at<double>(y, x) / matF_cnt.at<double>(y, x);

			cv::Vec3b a1;
			a1[2] = r;
			a1[1] = g;
			a1[0] = b;

			matAll.at<cv::Vec3b>(y, x) = a1;
		}
	}

	matRGB_out = matAll;


	return 0;
}

int kb::equalizeHist(
	cv::Mat& matF,
	cv::Mat& matF_out,
	float step_hist,//=1.0, 
	double ratio_sigma,//=0.1, 
	int window_size,//=80, 
	int window_step,//=20,
	int num_thread//=1
	//double sigma
)
{
	cv::Size sz1 = matF.size();

	int w1 = window_size;
	int w2 = window_step;
	float step = step_hist;
	if (step < 0.01) { step = 0.01; }

	if (w1 < 10) { w1 = 10; }
	if (w2 < 1) { w2 = 1; }
	else if (w1 < w2) { w2 = w1; }

	int n1 = (sz1.width - w1) / w2 + 1;
	int n2 = (sz1.height - w1) / w2 + 1;

	cv::Mat matF_r(sz1, CV_64F, cv::Scalar(0));
	cv::Mat matF_cnt(sz1, CV_64F, cv::Scalar(0));
	matF_out = cv::Mat(sz1, CV_32F, cv::Scalar(0));

	cv::Mat matF_wt(cv::Size(w1, w1), CV_64F, cv::Scalar(0));
	{
		int xm = w1 / 2;
		double wt0 = 2.0 * (xm * xm) * ratio_sigma;
		for (int jj = 0; jj < w1; jj++) {
			for (int ii = 0; ii < w1; ii++) {
				matF_wt.at<double>(jj, ii) = exp(-(double)((ii - xm) * (ii - xm) + (jj - xm) * (jj - xm)) / wt0);
			}
		}
	}

	int step_add_x = 0;
	int step_add_y = 0;
	{

		int x1_max = (n1 - 1) * w2 + w1;
		int y1_max = (n2 - 1) * w2 + w1;

		int amari_x = sz1.width - x1_max;
		int amari_y = sz1.height - y1_max;

		if (amari_x > 0 && n1 >= 2) {
			step_add_x = amari_x / (n1 - 1);
			if ((amari_x % (n1 - 1)) > 0) {
				step_add_x++;
			}
		}
		if (amari_y > 0 && n2 >= 2) {
			step_add_y = amari_y / (n2 - 1);
			if ((amari_y % (n2 - 1)) > 0) {
				step_add_y++;
			}
		}
		//std::cout << step_add_x << ", " << step_add_y << std::endl;

	}
	if (num_thread <= 1) {
		for (int j = 0; j < n2; j++) {
			for (int i = 0; i < n1; i++) {
				int x0 = i * (w2 + step_add_x); int x1 = x0 + w1;
				int y0 = j * (w2 + step_add_y); int y1 = y0 + w1;

				if (x1 >= sz1.width) { x1 = sz1.width; x0 = x1 - w1; }
				if (y1 >= sz1.height) { y1 = sz1.height; y0 = y1 - w1; }

				cv::Rect rect(x0, y0, w1, w1);

				cv::Mat mat1;
				matF(rect).copyTo(mat1);

				cv::Mat mat1_out;
				kb::equalizeHist_32F(mat1, mat1_out, step);

				for (int jj = 0; jj < w1; jj++) {
					for (int ii = 0; ii < w1; ii++) {
						double wt = matF_wt.at<double>(jj, ii);
						double a1 = mat1_out.at<float>(jj, ii);

						matF_r.at<double>(y0 + jj, x0 + ii) += (double)a1 * wt;
						matF_cnt.at<double>(y0 + jj, x0 + ii) += wt;
					}
				}
			}
		}

	}
	else {
		std::vector<cv::Mat> vec_mat;
		vec_mat.resize(n1 * n2);

#pragma omp parallel num_threads(num_thread)
		{
#pragma omp for 
			for (int j = 0; j < n2; j++) {
				for (int i = 0; i < n1; i++) {
					int x0 = i * (w2 + step_add_x); int x1 = x0 + w1;
					int y0 = j * (w2 + step_add_y); int y1 = y0 + w1;
					//int x0 = i * w2; int x1 = x0 + w1;
					//int y0 = j * w2; int y1 = y0 + w1;

					if (x1 >= sz1.width) { x1 = sz1.width; x0 = x1 - w1; }
					if (y1 >= sz1.height) { y1 = sz1.height; y0 = y1 - w1; }

					cv::Rect rect(x0, y0, w1, w1);

					cv::Mat mat1;
					matF(rect).copyTo(mat1);

					cv::Mat mat1_out;
					kb::equalizeHist_32F(mat1, mat1_out, step);

					vec_mat[i + j * n1] = mat1_out;
				}
			}
		}

		for (int j = 0; j < n2; j++) {
			for (int i = 0; i < n1; i++) {
				int x0 = i * (w2 + step_add_x); int x1 = x0 + w1;
				int y0 = j * (w2 + step_add_y); int y1 = y0 + w1;

				if (x1 >= sz1.width) { x1 = sz1.width; x0 = x1 - w1; }
				if (y1 >= sz1.height) { y1 = sz1.height; y0 = y1 - w1; }

				for (int jj = 0; jj < w1; jj++) {
					for (int ii = 0; ii < w1; ii++) {
						double wt = matF_wt.at<double>(jj, ii);

						double a1 = vec_mat[i + j * n1].at<float>(jj, ii);

						matF_r.at<double>(y0 + jj, x0 + ii) += a1 * wt;
						matF_cnt.at<double>(y0 + jj, x0 + ii) += wt;
					}
				}
			}
		}

	}

	for (int y = 0; y < sz1.height; y++) {
		for (int x = 0; x < sz1.width; x++) {
			if (matF_cnt.at<double>(y, x) < 0.0001)
				continue;
			matF_out.at<float>(y, x) = (float)(matF_r.at<double>(y, x) / matF_cnt.at<double>(y, x));
		}
	}


	return 0;
}


int kb::equalizeHist_32F(
	cv::Mat& matL, //	CV_32F
	cv::Mat& matL_out, //	CV_32F
	float step)
{
	cv::Size sz = matL.size();
	//	画像に含まれる総画素数
	int num = sz.width * sz.height;

	std::vector<float> hist1; kb::histogram256_32F(matL, hist1, step);

	//	ヒストグラムのビンの数
	int nbin = hist1.size();

	//	ひとつのビンあたりの平均
	double step2 = (double)num / (double)nbin;

	std::vector<float> lut1; lut1.resize(nbin, 0);

	float sum2 = 0;
	for (int i = 0; i < nbin; i++) {
		sum2 += hist1[i];

		double dx = step * sum2 / step2 - 1 - (float)i * step;
		lut1[i] = (float)i * step + dx * 0.5;
	}

	float v1_max = 0;
	matL.copyTo(matL_out);
	for (int j = 0; j < sz.height; j++) {
		for (int i = 0; i < sz.width; i++) {
			float v1 = matL.at<float>(j, i);
			if (v1_max < v1) { v1_max = v1; }
			int i1 = (int)(v1 / step);
			float w1 = v1 / step - (float)i1;

			float v2 = 0;
			if (i1 < 0) {
				v2 = lut1[0];
			}
			else if (i1 < (nbin - 1)) {
				v2 = lut1[i1] * (1.0 - w1) + lut1[i1 + 1] * w1;
			}
			else if (i1 >= (nbin - 1)) {
				v2 = lut1[nbin - 1];
			}
			if (v2 < 0.0) { v2 = 0.0; }
			else if (v2 > 255.0) { v2 = 255; }

			matL_out.at<float>(j, i) = v2;
		}
	}

	//std::cout<<"v1_max: "<<v1_max<<std::endl;

	return 0;
}

int kb::equalizeHist_32F(
	cv::Mat& matL, //	CV_32F
	cv::Mat& matL_out //	CV_32F
	)
{
	cv::Size sz = matL.size();
	//	画像に含まれる総画素数
	int num = sz.width * sz.height;

	std::vector<float> hist1; kb::histogram256_32F(matL, hist1);

	//	ヒストグラムのビンの数
	int nbin = hist1.size();

	//	ひとつのビンあたりの平均
	double step2 = (double)num / (double)nbin;

	std::vector<float> lut1; lut1.resize(nbin, 0);

	float sum2 = 0;
	for (int i = 0; i < nbin; i++) {
		sum2 += hist1[i];

		double dx = sum2 / step2 - 1 - (float)i;
		lut1[i] = (float)i + dx * 0.5;
	}

	float v1_max = 0;
	matL.copyTo(matL_out);
	for (int j = 0; j < sz.height; j++) {
		for (int i = 0; i < sz.width; i++) {
			float v1 = matL.at<float>(j, i);
			if (v1_max < v1) { v1_max = v1; }
			int i1 = (int)v1;
			float w1 = v1 - (float)i1;

			float v2 = 0;
			if (i1 < 0) {
				v2 = lut1[0];
			}
			else if (i1 < (nbin - 1)) {
				v2 = lut1[i1] * (1.0 - w1) + lut1[i1 + 1] * w1;
			}
			else if (i1 >= (nbin - 1)) {
				v2 = lut1[nbin - 1];
			}
			if (v2 < 0.0) { v2 = 0.0; }
			else if (v2 > 255.0) { v2 = 255; }

			matL_out.at<float>(j, i) = v2;
		}
	}

	//std::cout<<"v1_max: "<<v1_max<<std::endl;

	return 0;
}
