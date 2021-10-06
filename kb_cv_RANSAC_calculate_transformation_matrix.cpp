#define _USE_MATH_DEFINES
#include <math.h>

#include "kb_cv_RANSAC_calculate_transformation_matrix.h"
#include "kb_random.h"
#include <omp.h>

int kb::calculate_transformation_matrix_by_RANSAC(
	std::vector<cv::Point2f>& mp1,
	std::vector<cv::Point2f>& mp2,
	cv::Size& sz_img,
	cv::Mat& matAf,
	std::vector<cv::Point2f>& mp1_inlier,
	std::vector<cv::Point2f>& mp2_inlier,
	double threshold_dis1,
	int thres_max_valid_cnt,
	int RANSAC_iter_num,
	int numThread,
	double det_min,
	double det_max,
	double ratio_area,
	double threshold_ratio_delta_center,	//	�摜���S�̈ړ�������臒l�ݒ�
	double threshold_angle,					//	��]�p�x��臒l
	int mode
)
{

	int numX = mp1.size();
	std::cout << "num of inlier: " << numX << std::endl;


	//	RANSAC
	if (numX < thres_max_valid_cnt)
		return -1;

	double thres_dis2 = threshold_dis1 * threshold_dis1;
	int iter_num = RANSAC_iter_num;
	if (numThread <= 0) { numThread = 1; }
	double thres_det1 = det_min * det_min;
	double thres_det2 = det_max * det_max;
	//std::cout << "prm.m_threshold_dis1= " << prm.m_threshold_dis1 << std::endl;
	//std::cout << "prm.m_RANSAC_iter_num= " << prm.m_RANSAC_iter_num << std::endl;
	//std::cout << "prm.numThread= " << prm.numThread << std::endl;
	//std::cout << "prm.m_max_valid_cnt= " << prm.m_max_valid_cnt << std::endl;

	double thres_delta2_center = -1;
	double center[2] = { sz_img.width / 2, sz_img.height / 2 };
	if(threshold_ratio_delta_center>0.0){
		thres_delta2_center = threshold_ratio_delta_center * (sz_img.width + sz_img.height) / 2;
		//std::cout << "thres_delta2_center=" << thres_delta2_center << std::endl;
	}

	//	�摜�̐^�񒆕t�߂�D�悳���邽�߂̏���
	std::vector<int> v_flags_center;
	v_flags_center.resize(numX, 0);
	int cnt_center = 0;
	{
		if (ratio_area < 0.1) {
			ratio_area = 0.1;
		}
		else if (ratio_area > 1.0) {
			ratio_area = 1.0;
		}
		float w = (1.0 - ratio_area) * 0.5;

		float x1 = sz_img.width * w;
		float x2 = sz_img.width * (1.0 - w);
		float y1 = sz_img.height * w;
		float y2 = sz_img.height * (1.0 - w);
		for (int i = 0; i < numX; i++) {
			if (x1 < mp1[i].x && mp1[i].x < x2 && y1 < mp1[i].y && mp1[i].y < y2) {
				v_flags_center[i] = 1;
				cnt_center++;
			}
		}

		// ���S�Ɋ܂܂�鐔��10�ȉ��̏ꍇ�A�S��OK�ɂ���
		if (cnt_center < 10) {
			v_flags_center.clear();
			v_flags_center.resize(numX, 1);
		}
	}


	std::vector<int> rand_buf;
	rand_buf.resize(iter_num * 4, 0);
	if (cnt_center >= 10) {
		std::vector<int> lut2;
		lut2.resize(cnt_center);
		int ii = 0;
		for (int i = 0; i < numX; i++) {
			if (v_flags_center[i] > 0) {
				if (ii < cnt_center) {
					lut2[ii] = i;
				}

				ii++;
			}
		}


		for (int kk = 0; kk < iter_num; kk++) {
			int buf_idx[4];
			if (kb::getRandomNumbers(4, buf_idx, cnt_center) < 0)
				continue;
			for (int i = 0; i < 4; i++) {
				rand_buf[kk * 4 + i] = lut2[buf_idx[i]];
			}
		}
	}
	else {
		for (int kk = 0; kk < iter_num; kk++) {
			int buf[4];
			if (kb::getRandomNumbers(4, buf, numX) < 0)
				continue;

			for (int i = 0; i < 4; i++) {
				rand_buf[kk * 4 + i] = buf[i];
			}
		}
	}

	double threshold_cos = cos(M_PI * threshold_angle / 180.0);
	//double threshold_cos = cos(M_PI * 45.0 / 180.0);
	
	std::vector<cv::Mat> v_mat;
	std::vector<int> vec_max_valid_cnt;
	std::vector<std::vector<int>> vec_flags_max;

	vec_max_valid_cnt.resize(numThread, 0);
	vec_flags_max.resize(numThread);
	v_mat.resize(numThread);

	//std::cout << "start RANSAC" << std::endl;
#pragma omp parallel num_threads(numThread)
	{
#pragma omp for 
		for (int kk = 0; kk < iter_num; kk++) {
			int idx = omp_get_thread_num();

			std::vector<cv::Point2f> pts1v, pts2v;
			pts1v.resize(4); pts2v.resize(4);
			for (int ii = 0; ii < 4; ii++) {
				int i1 = rand_buf[kk * 4 + ii];

				pts1v[ii] = mp1[i1];
				pts2v[ii] = mp2[i1];
			}
			//
			cv::Mat matAf1;
			if (mode == 0) {
				//matAf1 = cv::estimateRigidTransform(pts1v, pts2v, false);
				matAf1 = cv::estimateAffinePartial2D(pts1v, pts2v);
			}
			else {
				matAf1 = cv::getPerspectiveTransform(pts1v, pts2v);
			}

			cv::Size szTM = matAf1.size();
			if (szTM.width <= 0 || szTM.height <= 0)
				continue;

			//	��]�p�x��臒l
			if(threshold_angle>0.0){
				double v[2] = { matAf1.at<double>(0, 0) ,matAf1.at<double>(1, 0) };
				double len_v = sqrt(v[0] * v[0] + v[1] * v[1]);
				double value_cos = v[0] / len_v;
				if (value_cos < threshold_cos)
					continue;
			}

			//	�摜���S�̈ړ��ʂ�臒l
			if(thres_delta2_center>0.0){
				double dx1 = matAf1.at<double>(0, 0) * center[0] + matAf1.at<double>(0, 1) * center[1] + matAf1.at<double>(0, 2) - center[0];
				double dy1 = matAf1.at<double>(1, 0) * center[0] + matAf1.at<double>(1, 1) * center[1] + matAf1.at<double>(1, 2) - center[1];
				double d1 = sqrt(dx1 * dx1 + dy1 * dy1);
				//std::cout << d1 << " ";// std::endl;
				if (d1 > thres_delta2_center) {
					continue;
				}
			}

			if (mode == 0) {
				double det1 = matAf1.at<double>(0, 0) * matAf1.at<double>(1, 1) - matAf1.at<double>(0, 1) * matAf1.at<double>(1, 0);
				if (det1 <= 0.0 || det1 < thres_det1 || thres_det2 < det1)
					continue;
			}
			else {
				double a[6] = {
					matAf1.at<double>(0, 0), matAf1.at<double>(1, 1),
					matAf1.at<double>(1, 0), matAf1.at<double>(0, 1),
					matAf1.at<double>(2, 0), matAf1.at<double>(2, 1)
				};
				double det0 = a[0] * a[1];
				if (det0 < 0.0)
					continue;

				//	
				double detP = a[0] * a[1] - a[2] * a[3];
				if (detP < 0.5)
					continue;

				for (int ii = 0; ii < 6; ii++) {
					if (a[ii] < 0.0) { a[ii] = -a[ii]; }
				}
				if (a[0] > 2.0 || a[1] > 2.0)
					continue;
				for (int ii = 0; ii < 3; ii++) {
					if (a[ii * 2] < a[ii * 2 + 1]) {
						double a2 = a[ii * 2];
						a[ii * 2] = a[ii * 2 + 1];
						a[ii * 2 + 1] = a2;
					}
				}
				int flag_x = 0;
				double thres0 = 1.0E-1;
				double ra[3] = { 1.0, 1.0, 1.0 };
				for (int ii = 0; ii < 2; ii++) {
					if (a[ii * 2] > thres0) {
						ra[ii] = a[ii * 2 + 1] / a[ii * 2];
						if (ra[ii] < 0.85) {
							flag_x++;
						}
					}
				}
				if (flag_x > 0)
					continue;

				ra[2] = a[5] / a[4];
				if (ra[2] < 0.5)
					continue;


			}

			//
			std::vector<int> flags;
			flags.resize(numX, 0);
			int valid_numX = 0;

			if (mode == 0) {
				for (int ii = 0; ii < numX; ii++) {
					double dx1 = matAf1.at<double>(0, 0) * mp1[ii].x + matAf1.at<double>(0, 1) * mp1[ii].y + matAf1.at<double>(0, 2) - mp2[ii].x;
					double dy1 = matAf1.at<double>(1, 0) * mp1[ii].x + matAf1.at<double>(1, 1) * mp1[ii].y + matAf1.at<double>(1, 2) - mp2[ii].y;

					double d2 = dx1 * dx1 + dy1 * dy1;
					if (d2 < thres_dis2) {
						valid_numX++;
						flags[ii] = 1;
					}
				}
			}
			else {
				for (int ii = 0; ii < numX; ii++) {
					double x1 = matAf1.at<double>(0, 0) * mp1[ii].x + matAf1.at<double>(0, 1) * mp1[ii].y + matAf1.at<double>(0, 2);
					double y1 = matAf1.at<double>(1, 0) * mp1[ii].x + matAf1.at<double>(1, 1) * mp1[ii].y + matAf1.at<double>(1, 2);
					double z1 = matAf1.at<double>(2, 0) * mp1[ii].x + matAf1.at<double>(2, 1) * mp1[ii].y + matAf1.at<double>(2, 2);

					double dx1 = x1 / z1 - mp2[ii].x;
					double dy1 = y1 / z1 - mp2[ii].y;

					double d2 = dx1 * dx1 + dy1 * dy1;
					if (d2 < thres_dis2) {
						valid_numX++;
						flags[ii] = 1;
					}
				}
			}

			if (vec_max_valid_cnt[idx] < valid_numX) {
				vec_flags_max[idx] = flags;
				vec_max_valid_cnt[idx] = valid_numX;
				matAf1.copyTo(v_mat[idx]);
			}
		}
	}

	std::vector<int> flags_max;
	int max_valid_cnt = 0;
	cv::Mat matAf_max;
	for (int k = 0; k < numThread; k++) {
		if (max_valid_cnt < vec_max_valid_cnt[k]) {
			max_valid_cnt = vec_max_valid_cnt[k];
			flags_max = vec_flags_max[k];
			matAf_max = v_mat[k];
		}
	}


	std::cout << "max_valid_cnt: " << max_valid_cnt << std::endl;
	matAf = cv::Mat::eye(3, 3, CV_64F);
	//std::cout << matAf_max << std::endl;
	//	
	if (max_valid_cnt < thres_max_valid_cnt) {
		return -1;
	}

	{
		mp1_inlier.resize(max_valid_cnt);
		mp2_inlier.resize(max_valid_cnt);
		int i = 0;
		for (int ii = 0; ii < numX; ii++) {
			if (flags_max[ii] == 0)
				continue;
			mp1_inlier[i] = mp1[ii];
			mp2_inlier[i] = mp2[ii];
			i++;
		}

		if (mode == 0) {
			//matAf_max = cv::estimateRigidTransform(mp1_inlier, mp2_inlier, false);
			matAf_max = cv::estimateAffinePartial2D(mp1_inlier, mp2_inlier);
		}
		else {
			//matAf_max = cv::findHomography(mp1_inlier, mp2_inlier);
			//matAf_max = cv::findHomography(mp1_inlier, mp2_inlier, CV_LMEDS);

			std::cout << matAf_max << std::endl;
		}
	}

	if (mode == 0) {
		matAf.at<double>(0, 0) = matAf_max.at<double>(0, 0);
		matAf.at<double>(0, 1) = matAf_max.at<double>(0, 1);
		matAf.at<double>(0, 2) = matAf_max.at<double>(0, 2);
		matAf.at<double>(1, 0) = matAf_max.at<double>(1, 0);
		matAf.at<double>(1, 1) = matAf_max.at<double>(1, 1);
		matAf.at<double>(1, 2) = matAf_max.at<double>(1, 2);
	}
	else {
		matAf_max.copyTo(matAf);
	}

	return 0;
}
