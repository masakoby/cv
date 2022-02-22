#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>

#include "kb_mat.h"
#include "kb_make_cube.h"

#pragma once

namespace kb
{


	class CUv2Cube
	{
	public:
		CUv2Cube(int mode)
		{
			double matX[9], matZ[9], matXZ[9];
			if (mode == 1) {
				kb::matRotX(matX, -90.0);
				kb::matRotZ(matZ, 90.0);
				kb::matmul_3x3_3x3(matZ, matX, matXZ);
			}
			else if (mode == 2) {
				kb::matRotX(matX, -90.0);
				kb::matRotZ(matZ, 0.0);
				kb::matmul_3x3_3x3(matZ, matX, matXZ);
			}
			else if (mode == 3) {
				kb::matRotX(matX, 180.0);
				kb::matRotZ(matZ, 90.0);
				kb::matmul_3x3_3x3(matZ, matX, matXZ);
			}
			else {
				kb::matRotX(matXZ, 0.0);
			}

			for (int k = 0; k < 6; k++) {
				double matR[9];
				//kb::make_cube_1face(cube_pt[k], matR, cube_idx[k], 2.0, k);
				kb::make_cube_1face_v2(cube_pt[k], matR, cube_idx[k], 2.0, k);
				
				kb::matmul_3x3_3x3(matXZ, matR, cube_matR[k]);
			}
		}

		int create(cv::Size szUV, int cx);
		int run_lut(cv::Mat& matUV, cv::Mat& matCube, int idx);
		int run_lut_inv(cv::Mat& matUV, cv::Mat& matCube, int idx, cv::Vec3b color_ov);

		double cube_pt[6][12], cube_matR[6][9];
		int cube_idx[6][4];

		cv::Size m_szUV;
		cv::Mat m_lut[6];
		cv::Mat m_lut_inv, m_lut_idx;
	};

};
