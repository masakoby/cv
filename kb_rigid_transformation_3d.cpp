#include "kb_rigid_transformation_3d.h"

//	対応点から、３次元の変換行列を求める
int kb::calculate_mat4x4(
	std::vector< double >& v_temp1,
	std::vector< double >& v_temp2,
	double* mat4x4,
	double* ratio_out
)
{
	int n1 = v_temp1.size() / 3;
	int n2 = v_temp2.size() / 3;
	{
		//std::cout<<"kb::calculate_mat4x4 : "<<n1<<std::endl;
		if (n1 < 3 || n1 != n2)
			return -1;
	}

	//	重心を求める
	double ptc1[3] = { 0,0,0 };
	double ptc2[3] = { 0,0,0 };
	for (int i = 0; i < n1; i++) {
		ptc1[0] += v_temp1[i * 3];
		ptc1[1] += v_temp1[i * 3 + 1];
		ptc1[2] += v_temp1[i * 3 + 2];
		ptc2[0] += v_temp2[i * 3];
		ptc2[1] += v_temp2[i * 3 + 1];
		ptc2[2] += v_temp2[i * 3 + 2];
	}
	for (int i = 0; i < 3; i++) {
		ptc1[i] /= (double)n1;
		ptc2[i] /= (double)n1;
	}

	//	重心位置を基準とした位置を求める
	std::vector< double > dv_temp1, dv_temp2;
	dv_temp1.resize(n1 * 3);
	dv_temp2.resize(n1 * 3);
	double sum1 = 0.0, sum2 = 0.0;
	for (int k = 0; k < n1; k++) {
		dv_temp1[k * 3 + 0] = v_temp1[k * 3 + 0] - ptc1[0];
		dv_temp1[k * 3 + 1] = v_temp1[k * 3 + 1] - ptc1[1];
		dv_temp1[k * 3 + 2] = v_temp1[k * 3 + 2] - ptc1[2];
		dv_temp2[k * 3 + 0] = v_temp2[k * 3 + 0] - ptc2[0];
		dv_temp2[k * 3 + 1] = v_temp2[k * 3 + 1] - ptc2[1];
		dv_temp2[k * 3 + 2] = v_temp2[k * 3 + 2] - ptc2[2];

		sum1 += sqrt(dv_temp1[k * 3 + 0] * dv_temp1[k * 3 + 0] + dv_temp1[k * 3 + 1] * dv_temp1[k * 3 + 1] + dv_temp1[k * 3 + 2] * dv_temp1[k * 3 + 2]);
		sum2 += sqrt(dv_temp2[k * 3 + 0] * dv_temp2[k * 3 + 0] + dv_temp2[k * 3 + 1] * dv_temp2[k * 3 + 1] + dv_temp2[k * 3 + 2] * dv_temp2[k * 3 + 2]);
	}
	double ratio = sum1 / sum2;
	for (int k = 0; k < n1; k++) {
		dv_temp2[k * 3 + 0] = dv_temp2[k * 3 + 0] * ratio;
		dv_temp2[k * 3 + 1] = dv_temp2[k * 3 + 1] * ratio;
		dv_temp2[k * 3 + 2] = dv_temp2[k * 3 + 2] * ratio;
	}

	//	X*Yt
	cv::Mat matX(3, n1, CV_64FC1, cv::Scalar(0.0));
	cv::Mat matY(3, n1, CV_64FC1, cv::Scalar(0.0));

	for (int k = 0; k < n1; k++) {
		matX.at<double>(0, k) = dv_temp1[k * 3];
		matX.at<double>(1, k) = dv_temp1[k * 3 + 1];
		matX.at<double>(2, k) = dv_temp1[k * 3 + 2];
		matY.at<double>(0, k) = dv_temp2[k * 3];
		matY.at<double>(1, k) = dv_temp2[k * 3 + 1];
		matY.at<double>(2, k) = dv_temp2[k * 3 + 2];
	}

	cv::Mat matXYt(3, 3, CV_64FC1, cv::Scalar(0.0));
	cv::Mat matTemp;
	cv::gemm(matX, matY, 1.0, matTemp, 0.0, matXYt, cv::GEMM_2_T);


	//
	cv::Mat matR(3, 3, CV_64FC1, cv::Scalar(0.0));
	{
		cv::SVD obj(matXYt, cv::SVD::FULL_UV);

		cv::Mat matVUt(3, 3, CV_64FC1, cv::Scalar(0.0));
		cv::gemm(obj.vt, obj.u, 1.0, matTemp, 0.0, matVUt, cv::GEMM_1_T | cv::GEMM_2_T);
		cv::Mat matH(3, 3, CV_64FC1, cv::Scalar(0.0));
		double det = cv::determinant(matVUt);
		matH.at<double>(0, 0) = 1.0;
		matH.at<double>(1, 1) = 1.0;
		matH.at<double>(2, 2) = det;

		cv::Mat matVH(3, 3, CV_64FC1, cv::Scalar(0.0));
		cv::gemm(obj.vt, matH, 1.0, matTemp, 0.0, matVH, cv::GEMM_1_T);
		cv::Mat matVHUt(3, 3, CV_64FC1, cv::Scalar(0.0));
		cv::gemm(matVH, obj.u, 1.0, matTemp, 0.0, matVHUt, cv::GEMM_2_T);

		matVHUt.copyTo(matR);
	}


	mat4x4[0] = matR.at<double>(0, 0);
	mat4x4[1] = matR.at<double>(0, 1);
	mat4x4[2] = matR.at<double>(0, 2);
	mat4x4[4] = matR.at<double>(1, 0);
	mat4x4[5] = matR.at<double>(1, 1);
	mat4x4[6] = matR.at<double>(1, 2);
	mat4x4[8] = matR.at<double>(2, 0);
	mat4x4[9] = matR.at<double>(2, 1);
	mat4x4[10] = matR.at<double>(2, 2);

	mat4x4[3] = ptc2[0] - (matR.at<double>(0, 0) * ptc1[0] + matR.at<double>(0, 1) * ptc1[1] + matR.at<double>(0, 2) * ptc1[2]);
	mat4x4[7] = ptc2[1] - (matR.at<double>(1, 0) * ptc1[0] + matR.at<double>(1, 1) * ptc1[1] + matR.at<double>(1, 2) * ptc1[2]);
	mat4x4[11] = ptc2[2] - (matR.at<double>(2, 0) * ptc1[0] + matR.at<double>(2, 1) * ptc1[1] + matR.at<double>(2, 2) * ptc1[2]);

	mat4x4[12] = 0.0;
	mat4x4[13] = 0.0;
	mat4x4[14] = 0.0;
	mat4x4[15] = 1.0;

	*ratio_out = ratio;
	return 0;
}

	//	対応点から、３次元の変換行列を求める
	int kb::calculate_mat4x4(
		std::vector< double >& v_temp1,
		std::vector< double >& v_temp2,
		double* mat4x4
	)
	{
		int n1 = v_temp1.size() / 3;
		int n2 = v_temp2.size() / 3;
		{
			//std::cout<<"kb::calculate_mat4x4 : "<<n1<<std::endl;
			if (n1 < 3 || n1 != n2)
				return -1;
		}

		//	重心を求める
		double ptc1[3] = { 0,0,0 };
		double ptc2[3] = { 0,0,0 };
		for (int i = 0; i < n1; i++) {
			ptc1[0] += v_temp1[i * 3];
			ptc1[1] += v_temp1[i * 3 + 1];
			ptc1[2] += v_temp1[i * 3 + 2];
			ptc2[0] += v_temp2[i * 3];
			ptc2[1] += v_temp2[i * 3 + 1];
			ptc2[2] += v_temp2[i * 3 + 2];
		}
		for (int i = 0; i < 3; i++) {
			ptc1[i] /= (double)n1;
			ptc2[i] /= (double)n1;
		}

		//	重心位置を基準とした位置を求める
		std::vector< double > dv_temp1, dv_temp2;
		for (int k = 0; k < n1; k++) {
			dv_temp1.push_back(v_temp1[k * 3] - ptc1[0]);
			dv_temp1.push_back(v_temp1[k * 3 + 1] - ptc1[1]);
			dv_temp1.push_back(v_temp1[k * 3 + 2] - ptc1[2]);
			dv_temp2.push_back(v_temp2[k * 3] - ptc2[0]);
			dv_temp2.push_back(v_temp2[k * 3 + 1] - ptc2[1]);
			dv_temp2.push_back(v_temp2[k * 3 + 2] - ptc2[2]);
		}


		//	X*Yt
		cv::Mat matX(3, n1, CV_64FC1, cv::Scalar(0.0));
		cv::Mat matY(3, n1, CV_64FC1, cv::Scalar(0.0));

		for (int k = 0; k < n1; k++) {
			matX.at<double>(0, k) = dv_temp1[k * 3];
			matX.at<double>(1, k) = dv_temp1[k * 3 + 1];
			matX.at<double>(2, k) = dv_temp1[k * 3 + 2];
			matY.at<double>(0, k) = dv_temp2[k * 3];
			matY.at<double>(1, k) = dv_temp2[k * 3 + 1];
			matY.at<double>(2, k) = dv_temp2[k * 3 + 2];
		}

		cv::Mat matXYt(3, 3, CV_64FC1, cv::Scalar(0.0));
		cv::Mat matTemp;
		cv::gemm(matX, matY, 1.0, matTemp, 0.0, matXYt, cv::GEMM_2_T);


		//
		cv::Mat matR(3, 3, CV_64FC1, cv::Scalar(0.0));
		{
			cv::SVD obj(matXYt, cv::SVD::FULL_UV);

			cv::Mat matVUt(3, 3, CV_64FC1, cv::Scalar(0.0));
			cv::gemm(obj.vt, obj.u, 1.0, matTemp, 0.0, matVUt, cv::GEMM_1_T | cv::GEMM_2_T);
			cv::Mat matH(3, 3, CV_64FC1, cv::Scalar(0.0));
			double det = cv::determinant(matVUt);
			matH.at<double>(0, 0) = 1.0;
			matH.at<double>(1, 1) = 1.0;
			matH.at<double>(2, 2) = det;

			cv::Mat matVH(3, 3, CV_64FC1, cv::Scalar(0.0));
			cv::gemm(obj.vt, matH, 1.0, matTemp, 0.0, matVH, cv::GEMM_1_T);
			cv::Mat matVHUt(3, 3, CV_64FC1, cv::Scalar(0.0));
			cv::gemm(matVH, obj.u, 1.0, matTemp, 0.0, matVHUt, cv::GEMM_2_T);

			matVHUt.copyTo(matR);
		}


		mat4x4[0] = matR.at<double>(0, 0);
		mat4x4[1] = matR.at<double>(0, 1);
		mat4x4[2] = matR.at<double>(0, 2);
		mat4x4[4] = matR.at<double>(1, 0);
		mat4x4[5] = matR.at<double>(1, 1);
		mat4x4[6] = matR.at<double>(1, 2);
		mat4x4[8] = matR.at<double>(2, 0);
		mat4x4[9] = matR.at<double>(2, 1);
		mat4x4[10] = matR.at<double>(2, 2);

		mat4x4[3] = ptc2[0] - (matR.at<double>(0, 0) * ptc1[0] + matR.at<double>(0, 1) * ptc1[1] + matR.at<double>(0, 2) * ptc1[2]);
		mat4x4[7] = ptc2[1] - (matR.at<double>(1, 0) * ptc1[0] + matR.at<double>(1, 1) * ptc1[1] + matR.at<double>(1, 2) * ptc1[2]);
		mat4x4[11] = ptc2[2] - (matR.at<double>(2, 0) * ptc1[0] + matR.at<double>(2, 1) * ptc1[1] + matR.at<double>(2, 2) * ptc1[2]);

		mat4x4[12] = 0.0;
		mat4x4[13] = 0.0;
		mat4x4[14] = 0.0;
		mat4x4[15] = 1.0;
		return 0;
	}

	//	対応点から、３次元の回転変換行列を求める
	int kb::calculate_matR3x3(
		std::vector< double >& v_temp1,
		std::vector< double >& v_temp2,
		double* mat3x3
	)
	{
		int n1 = v_temp1.size() / 3;
		int n2 = v_temp2.size() / 3;
		{
			//std::cout<<"kb::calculate_mat4x4 : "<<n1<<std::endl;
			if (n1 < 3 || n1 != n2)
				return -1;
		}


		//	X*Yt
		cv::Mat matX(3, n1, CV_64FC1, cv::Scalar(0.0));
		cv::Mat matY(3, n1, CV_64FC1, cv::Scalar(0.0));

		for (int k = 0; k < n1; k++) {
			matX.at<double>(0, k) = v_temp1[k * 3];
			matX.at<double>(1, k) = v_temp1[k * 3 + 1];
			matX.at<double>(2, k) = v_temp1[k * 3 + 2];
			matY.at<double>(0, k) = v_temp2[k * 3];
			matY.at<double>(1, k) = v_temp2[k * 3 + 1];
			matY.at<double>(2, k) = v_temp2[k * 3 + 2];
		}

		cv::Mat matXYt(3, 3, CV_64FC1, cv::Scalar(0.0));
		cv::Mat matTemp;
		cv::gemm(matX, matY, 1.0, matTemp, 0.0, matXYt, cv::GEMM_2_T);


		//
		cv::Mat matR(3, 3, CV_64FC1, cv::Scalar(0.0));
		{
			cv::SVD obj(matXYt, cv::SVD::FULL_UV);

			cv::Mat matVUt(3, 3, CV_64FC1, cv::Scalar(0.0));
			cv::gemm(obj.vt, obj.u, 1.0, matTemp, 0.0, matVUt, cv::GEMM_1_T | cv::GEMM_2_T);
			cv::Mat matH(3, 3, CV_64FC1, cv::Scalar(0.0));
			double det = cv::determinant(matVUt);
			matH.at<double>(0, 0) = 1.0;
			matH.at<double>(1, 1) = 1.0;
			matH.at<double>(2, 2) = det;

			cv::Mat matVH(3, 3, CV_64FC1, cv::Scalar(0.0));
			cv::gemm(obj.vt, matH, 1.0, matTemp, 0.0, matVH, cv::GEMM_1_T);
			cv::Mat matVHUt(3, 3, CV_64FC1, cv::Scalar(0.0));
			cv::gemm(matVH, obj.u, 1.0, matTemp, 0.0, matVHUt, cv::GEMM_2_T);

			matVHUt.copyTo(matR);
		}


		mat3x3[0] = matR.at<double>(0, 0);
		mat3x3[1] = matR.at<double>(0, 1);
		mat3x3[2] = matR.at<double>(0, 2);
		mat3x3[3] = matR.at<double>(1, 0);
		mat3x3[4] = matR.at<double>(1, 1);
		mat3x3[5] = matR.at<double>(1, 2);
		mat3x3[6] = matR.at<double>(2, 0);
		mat3x3[7] = matR.at<double>(2, 1);
		mat3x3[8] = matR.at<double>(2, 2);


		return 0;
	}

	//	対応点から、３次元の変換行列を求める
	int kb::calculate_mat4x4_with_constrained_point(
		std::vector< double >& v_temp1,
		std::vector< double >& v_temp2,
		double* mat4x4
	)
	{
		int n1 = v_temp1.size()/3;
		int n2 = v_temp2.size()/3;
		{
			if (n1 < 3 || n1 != n2)
				return -1;
		}

		//	先頭の点を不動点とする
		//mist::vector3<double> ptc1(0, 0, 0), ptc2(0, 0, 0);
		//ptc1 = v_temp1[0];
		//ptc2 = v_temp2[0];


		//	先頭の点を基準とした位置を求める
		std::vector< double > dv_temp1, dv_temp2;
		for (int k = 0; k < n1; k++) {
			int k3 = k * 3;
			dv_temp1.push_back(v_temp1[k3 + 0] - v_temp1[0]);
			dv_temp1.push_back(v_temp1[k3 + 1] - v_temp1[1]);
			dv_temp1.push_back(v_temp1[k3 + 2] - v_temp1[2]);
			dv_temp2.push_back(v_temp2[k3 + 0] - v_temp2[0]);
			dv_temp2.push_back(v_temp2[k3 + 1] - v_temp2[1]);
			dv_temp2.push_back(v_temp2[k3 + 2] - v_temp2[2]);
		}


		//	X*Yt
		cv::Mat matX(3, n1, CV_64FC1, cv::Scalar(0.0));
		cv::Mat matY(3, n1, CV_64FC1, cv::Scalar(0.0));

		for (int k = 0; k < n1; k++) {
			int k3 = k * 3;
			matX.at<double>(0, k) = dv_temp1[k3 + 0];
			matX.at<double>(1, k) = dv_temp1[k3 + 1];
			matX.at<double>(2, k) = dv_temp1[k3 + 2];
			matY.at<double>(0, k) = dv_temp2[k3 + 0];
			matY.at<double>(1, k) = dv_temp2[k3 + 1];
			matY.at<double>(2, k) = dv_temp2[k3 + 2];
		}

		cv::Mat matXYt(3, 3, CV_64FC1, cv::Scalar(0.0));
		cv::Mat matTemp;
		cv::gemm(matX, matY, 1.0, matTemp, 0.0, matXYt, cv::GEMM_2_T);


		//
		cv::Mat matR(3, 3, CV_64FC1, cv::Scalar(0.0));
		{
			cv::SVD obj(matXYt, cv::SVD::FULL_UV);

			cv::Mat matVUt(3, 3, CV_64FC1, cv::Scalar(0.0));
			cv::gemm(obj.vt, obj.u, 1.0, matTemp, 0.0, matVUt, cv::GEMM_1_T | cv::GEMM_2_T);
			cv::Mat matH(3, 3, CV_64FC1, cv::Scalar(0.0));
			double det = cv::determinant(matVUt);
			matH.at<double>(0, 0) = 1.0;
			matH.at<double>(1, 1) = 1.0;
			matH.at<double>(2, 2) = det;

			cv::Mat matVH(3, 3, CV_64FC1, cv::Scalar(0.0));
			cv::gemm(obj.vt, matH, 1.0, matTemp, 0.0, matVH, cv::GEMM_1_T);
			cv::Mat matVHUt(3, 3, CV_64FC1, cv::Scalar(0.0));
			cv::gemm(matVH, obj.u, 1.0, matTemp, 0.0, matVHUt, cv::GEMM_2_T);

			matVHUt.copyTo(matR);
		}


		mat4x4[0] = matR.at<double>(0, 0);
		mat4x4[1] = matR.at<double>(0, 1);
		mat4x4[2] = matR.at<double>(0, 2);
		mat4x4[4] = matR.at<double>(1, 0);
		mat4x4[5] = matR.at<double>(1, 1);
		mat4x4[6] = matR.at<double>(1, 2);
		mat4x4[8] = matR.at<double>(2, 0);
		mat4x4[9] = matR.at<double>(2, 1);
		mat4x4[10] = matR.at<double>(2, 2);

		mat4x4[3] = v_temp2[0] - (matR.at<double>(0, 0) * v_temp1[0] + matR.at<double>(0, 1) * v_temp1[1] + matR.at<double>(0, 2) * v_temp1[2]);
		mat4x4[7] = v_temp2[1] - (matR.at<double>(1, 0) * v_temp1[0] + matR.at<double>(1, 1) * v_temp1[1] + matR.at<double>(1, 2) * v_temp1[2]);
		mat4x4[11] = v_temp2[2] - (matR.at<double>(2, 0) * v_temp1[0] + matR.at<double>(2, 1) * v_temp1[1] + matR.at<double>(2, 2) * v_temp1[2]);

		mat4x4[12] = 0.0;
		mat4x4[13] = 0.0;
		mat4x4[14] = 0.0;
		mat4x4[15] = 1.0;
		return 0;
	}
