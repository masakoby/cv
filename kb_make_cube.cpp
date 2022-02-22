#include "kb_make_cube.h"
#include "kb_mat.h"

int kb::make_cube_1face(std::vector<double>& vec_pos, std::vector<int>& vec_idx, double length, int face0to5)
{
	double pt[9][3] = {
		0.0, 0.0, 1.0,
		1.0, 0.0, 1.0,
		1.0, 1.0, 1.0,
		0.0, 1.0, 1.0,
		-1.0, 1.0, 1.0,
		-1.0, 0.0, 1.0,
		-1.0, -1.0, 1.0,
		0.0, -1.0, 1.0,
		1.0, -1.0, 1.0
	};

	int idx[8][3] = {
		0,1,2,
		0,2,3,
		0,3,4,
		0,4,5,
		0,5,6,
		0,6,7,
		0,7,8,
		0,8,1
	};
	double r = length * 0.5;

	int num_pt = 9;
	int num_triangle = 8;
	vec_pos.resize(num_pt * 3);
	vec_idx.resize(num_triangle * 3);

	double matR[9] = { 1,0,0,0,1,0,0,0,1 };
	if (face0to5 == 1) {
		kb::matRotY(matR, 90.0);
	}
	else if (face0to5 == 2) {
		kb::matRotX(matR, -90.0);
	}
	else if (face0to5 == 3) {
		kb::matRotY(matR, -90.0);
	}
	else if (face0to5 == 4) {
		kb::matRotX(matR, 90.0);
	}
	else if (face0to5 == 5) {
		kb::matRotX(matR, 180.0);
	}

	for (int i = 0; i < num_pt; i++) {
		double p1[3] = {
			pt[i][0] * r, pt[i][1] * r, pt[i][2] * r
		};
		double p2[3];
		kb::matmul_3x3_3x1(matR, p1, p2);

		vec_pos[i * 3] = p2[0];
		vec_pos[i * 3 + 1] = p2[1];
		vec_pos[i * 3 + 2] = p2[2];
	}

	for (int i = 0; i < num_triangle; i++) {
		vec_idx[i * 3] = idx[i][0];
		vec_idx[i * 3 + 1] = idx[i][1];
		vec_idx[i * 3 + 2] = idx[i][2];
	}


	return 0;
}

int kb::dirvector_cube_1face(double vec_pos[3], int face0to5)
{
	double pt[3] = { 0,0,1 };

	double matR[9] = { 1,0,0,0,1,0,0,0,1 };
	if (face0to5 == 1) {
		kb::matRotY(matR, 90.0);
	}
	else if (face0to5 == 2) {
		kb::matRotX(matR, -90.0);
	}
	else if (face0to5 == 3) {
		kb::matRotY(matR, -90.0);
	}
	else if (face0to5 == 4) {
		kb::matRotX(matR, 90.0);
	}
	else if (face0to5 == 5) {
		kb::matRotX(matR, 180.0);
	}

	kb::matmul_3x3_3x1(matR, pt, vec_pos);
	return 0;
}

int kb::make_cube_1face(double vec_pos[12], double matR1[9], int vec_idx[4], double length, int face0to5)
{
	double pt[4][3] = {
		1.0, 1.0, 1.0,
		-1.0, 1.0, 1.0,
		-1.0, -1.0, 1.0,
		1.0, -1.0, 1.0
	};

	int idx[4] = {
		0,1,2,3
	};
	double r = length * 0.5;

	int num_pt = 4;

	double matR[9] = { 1,0,0,0,1,0,0,0,1 };
	if (face0to5 == 1) {
		kb::matRotY(matR, 90.0);
	}
	else if (face0to5 == 2) {
		kb::matRotX(matR, -90.0);
	}
	else if (face0to5 == 3) {
		kb::matRotY(matR, -90.0);
	}
	else if (face0to5 == 4) {
		kb::matRotX(matR, 90.0);
	}
	else if (face0to5 == 5) {
		kb::matRotX(matR, 180.0);
	}

	for (int i = 0; i < num_pt; i++) {
		double p1[3] = {
			pt[i][0] * r, pt[i][1] * r, pt[i][2] * r
		};
		double p2[3];
		kb::matmul_3x3_3x1(matR, p1, p2);

		vec_pos[i * 3] = p2[0];
		vec_pos[i * 3 + 1] = p2[1];
		vec_pos[i * 3 + 2] = p2[2];
	}

	for (int i = 0; i < 9; i++) {
		matR1[i] = matR[i];
	}

	for (int i = 0; i < 4; i++) {
		vec_idx[i] = idx[i];
	}

	return 0;
}

int kb::make_cube_1face_v2(double vec_pos[12], double matR1[9], int vec_idx[4], double length, int face0to5)
{
	double pt[4][3] = {
		1.0, 1.0, 1.0,
		-1.0, 1.0, 1.0,
		-1.0, -1.0, 1.0,
		1.0, -1.0, 1.0
	};

	int idx[4] = {
		0,1,2,3
	};
	double r = length * 0.5;

	int num_pt = 4;

	double matR[9] = { 1,0,0,0,1,0,0,0,1 };
	if (face0to5 == 1) {
		kb::matRotY(matR, 90.0);
	}
	else if (face0to5 == 2) {
		kb::matRotX(matR, -90.0);
	}
	else if (face0to5 == 3) {
		kb::matRotY(matR, -90.0);
	}
	else if (face0to5 == 4) {
		kb::matRotX(matR, 90.0);
	}
	else if (face0to5 == 5) {
		kb::matRotY(matR, 180.0);
	}

	for (int i = 0; i < num_pt; i++) {
		double p1[3] = {
			pt[i][0] * r, pt[i][1] * r, pt[i][2] * r
		};
		double p2[3];
		kb::matmul_3x3_3x1(matR, p1, p2);

		vec_pos[i * 3] = p2[0];
		vec_pos[i * 3 + 1] = p2[1];
		vec_pos[i * 3 + 2] = p2[2];
	}

	for (int i = 0; i < 9; i++) {
		matR1[i] = matR[i];
	}

	for (int i = 0; i < 4; i++) {
		vec_idx[i] = idx[i];
	}

	return 0;
}

