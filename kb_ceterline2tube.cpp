#define _USE_MATH_DEFINES
#include <math.h>

#include "kb_ceterline2tube.h"
#include "kb_orhogonal_vectors.h"
#include "kb_mat.h"
#include <iostream>

int kb::centerline2tube(
	std::vector<double>& o_vec_pos,
	std::vector<double>& o_vec_vz,
	std::vector<double>& o_vec_r,
	int num_sample,
	std::vector<double>& circum
)
{
	int numPt = o_vec_pos.size() / 3;


	std::cout << "num of centerline: " << numPt << std::endl;
	std::cout << "num of circle: " << num_sample << std::endl;
	{
		int num2 = o_vec_vz.size() / 3;
		std::cout << "buffer check, vec_vz: " << num2 << std::endl;
	}
	{
		int num2 = o_vec_r.size();
		std::cout << "buffer check, vec_r: " << num2 << std::endl;
	}


	double vx0[3], vy0[3], vz0[3];

	for (int k = 0; k < numPt; k++) {
		//------------------------------------------
		//	スプライン中心線から点と方向ベクトルをピックアップする
		//	垂直断面の平面を取得する
		double plane_pos[3] = { o_vec_pos[k * 3], o_vec_pos[k * 3 + 1], o_vec_pos[k * 3 + 2] };

		double plane_dir[3] = { o_vec_vz[k * 3], o_vec_vz[k * 3 + 1], o_vec_vz[k * 3 + 2] };


		//------------------------------------------
		//	垂直断面のＸＹ軸ベクトルを取得
		double plane_vx[3], plane_vy[3];

		if (k == 0) {
			kb::orthogonalVectors(plane_dir, plane_vx, plane_vy);
		}
		else {
			kb::orthogonalVectors(vx0, vy0, vz0, plane_dir, plane_vx, plane_vy);
		}


		double radius = o_vec_r[k];

		//------------------------------------------
		//	断面座標を取得する
		{
			for (int jj = 0; jj < num_sample; jj++) {
				double rad = 2.0 * M_PI * (double)jj / (double)num_sample;

				double c1 = radius * cos(rad);
				double s1 = radius * sin(rad);
				double dir[3]; kb::addWeighted(plane_vx, c1, plane_vy, s1, dir, 3);

				double xx = plane_pos[0] + dir[0];
				double yy = plane_pos[1] + dir[1];
				double zz = plane_pos[2] + dir[2];

				circum.push_back(xx);
				circum.push_back(yy);
				circum.push_back(zz);
			}
		}

		kb::copy(plane_vx, vx0, 3);
		kb::copy(plane_vy, vy0, 3);
		kb::copy(plane_dir, vz0, 3);

	}

	return 0;
}

int kb::tube2tube(
	std::vector<double>& circum,
	std::vector<double>& vec_vz,
	int num_sample,
	std::vector<double>& o_circum,
	int max_iter
)
{
	int num_line = circum.size() / (num_sample * 3);

	std::vector<double> vc = circum;
	std::vector<double> vc2 = circum;
	int iter = 0;
	//int max_iter = 3;
	while (iter<max_iter) {
		for (int j = 0; j < num_sample; j++) {
			for (int k = 1; k < num_line - 1; k++) {
				int k1 = (k - 1) * num_sample + j;
				int k2 = k * num_sample + j;
				int k3 = (k + 1) * num_sample + j;

				vc2[k2 * 3 + 0] = (vc[k1 * 3 + 0] + vc[k2 * 3 + 0] + vc[k3 * 3 + 0]) / 3.0;
				vc2[k2 * 3 + 1] = (vc[k1 * 3 + 1] + vc[k2 * 3 + 1] + vc[k3 * 3 + 1]) / 3.0;
				vc2[k2 * 3 + 2] = (vc[k1 * 3 + 2] + vc[k2 * 3 + 2] + vc[k3 * 3 + 2]) / 3.0;
			}
		}
		vc = vc2;
		iter++;		
	}

	o_circum = vc;

	return 0;
}
