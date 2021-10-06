#define _USE_MATH_DEFINES
#include <math.h>
#include <fstream> 

#include "kb_mat.h"

void kb::matRotZ(double* mat3x3, double deg)
{
	double radZ = deg * M_PI / 180.0;
	mat3x3[0] = cos(radZ);
	mat3x3[1] = -sin(radZ);
	mat3x3[2] = 0.0;
	mat3x3[3] = sin(radZ);
	mat3x3[4] = cos(radZ);
	mat3x3[5] = 0.0;
	mat3x3[6] = 0.0;
	mat3x3[7] = 0.0;
	mat3x3[8] = 1.0;
}

void kb::matRotX(double* mat3x3, double deg)
{
	double radZ = deg * M_PI / 180.0;
	mat3x3[0] = 1.0;
	mat3x3[1] = 0.0;
	mat3x3[2] = 0.0;
	mat3x3[3] = 0.0;
	mat3x3[4] = cos(radZ);
	mat3x3[5] = -sin(radZ);
	mat3x3[6] = 0.0;
	mat3x3[7] = sin(radZ);
	mat3x3[8] = cos(radZ);
}

void kb::matRotY(double* mat3x3, double deg)
{
	double radZ = deg * M_PI / 180.0;
	mat3x3[0] = cos(radZ);
	mat3x3[1] = 0.0;
	mat3x3[2] = sin(radZ);
	mat3x3[3] = 0.0;
	mat3x3[4] = 1.0;
	mat3x3[5] = 0.0;
	mat3x3[6] = -sin(radZ);
	mat3x3[7] = 0;
	mat3x3[8] = cos(radZ);
}

void kb::matmul_3x3_3x1(double* mat1, double* vec1, double* vec2)
{
	vec2[0] = mat1[0] * vec1[0] + mat1[1] * vec1[1] + mat1[2] * vec1[2];
	vec2[1] = mat1[3] * vec1[0] + mat1[4] * vec1[1] + mat1[5] * vec1[2];
	vec2[2] = mat1[6] * vec1[0] + mat1[7] * vec1[1] + mat1[8] * vec1[2];
}

void kb::matmul_3x3_3x3(double* mat1, double* mat2, double* mat3)
{
	for (int i = 0; i < 3; i++) {
		int k = i * 3;
		mat3[0 + k] = mat2[0] * mat1[0 + k] + mat2[3] * mat1[1 + k] + mat2[6] * mat1[2 + k];
		mat3[1 + k] = mat2[1] * mat1[0 + k] + mat2[4] * mat1[1 + k] + mat2[7] * mat1[2 + k];
		mat3[2 + k] = mat2[2] * mat1[0 + k] + mat2[5] * mat1[1 + k] + mat2[8] * mat1[2 + k];
	}
}

void kb::matmul_1x3_3x3(double* vec1, double* mat1, double* vec2)
{
	vec2[0] = mat1[0] * vec1[0] + mat1[3] * vec1[1] + mat1[6] * vec1[2];
	vec2[1] = mat1[1] * vec1[0] + mat1[4] * vec1[1] + mat1[7] * vec1[2];
	vec2[2] = mat1[2] * vec1[0] + mat1[5] * vec1[1] + mat1[8] * vec1[2];
}

void kb::matmul_4x4_4x1(const double* mat1, const double* vec1, double* vec2)
{
	vec2[0] = mat1[0] * vec1[0] + mat1[1] * vec1[1] + mat1[2] * vec1[2] + mat1[3] * vec1[3];
	vec2[1] = mat1[4] * vec1[0] + mat1[5] * vec1[1] + mat1[6] * vec1[2] + mat1[7] * vec1[3];
	vec2[2] = mat1[8] * vec1[0] + mat1[9] * vec1[1] + mat1[10] * vec1[2] + mat1[11] * vec1[3];
	vec2[3] = mat1[12] * vec1[0] + mat1[13] * vec1[1] + mat1[14] * vec1[2] + mat1[15] * vec1[3];
}

void kb::matmul_1x4_4x4(double* vec1, double* mat1, double* vec2)
{
	vec2[0] = mat1[0] * vec1[0] + mat1[4] * vec1[1] + mat1[8] * vec1[2] + mat1[12] * vec1[3];
	vec2[1] = mat1[1] * vec1[0] + mat1[5] * vec1[1] + mat1[9] * vec1[2] + mat1[13] * vec1[3];
	vec2[2] = mat1[2] * vec1[0] + mat1[6] * vec1[1] + mat1[10] * vec1[2] + mat1[14] * vec1[3];
	vec2[3] = mat1[3] * vec1[0] + mat1[7] * vec1[1] + mat1[11] * vec1[2] + mat1[15] * vec1[3];
}

void kb::matmul_4x4_4x4(double* mat1, double* mat2, double* mat3)
{
	for (int i = 0; i < 4; i++) {
		int k = i * 4;
		mat3[0 + k] = mat2[0] * mat1[0 + k] + mat2[4] * mat1[1 + k] + mat2[8] * mat1[2 + k] + mat2[12] * mat1[3 + k];
		mat3[1 + k] = mat2[1] * mat1[0 + k] + mat2[5] * mat1[1 + k] + mat2[9] * mat1[2 + k] + mat2[13] * mat1[3 + k];
		mat3[2 + k] = mat2[2] * mat1[0 + k] + mat2[6] * mat1[1 + k] + mat2[10] * mat1[2 + k] + mat2[14] * mat1[3 + k];
		mat3[3 + k] = mat2[3] * mat1[0 + k] + mat2[7] * mat1[1 + k] + mat2[11] * mat1[2 + k] + mat2[15] * mat1[3 + k];
	}
}

void kb::mat4x4inverse(double* mat4x4, double* mat4x4_o)
{
	mat4x4_o[0] = mat4x4[0];
	mat4x4_o[1] = mat4x4[4];
	mat4x4_o[2] = mat4x4[8];

	mat4x4_o[4] = mat4x4[1];
	mat4x4_o[5] = mat4x4[5];
	mat4x4_o[6] = mat4x4[9];

	mat4x4_o[8] = mat4x4[2];
	mat4x4_o[9] = mat4x4[6];
	mat4x4_o[10] = mat4x4[10];

	mat4x4_o[3] = -mat4x4[0] * mat4x4[3] - mat4x4[4] * mat4x4[7] - mat4x4[8] * mat4x4[11];
	mat4x4_o[7] = -mat4x4[1] * mat4x4[3] - mat4x4[5] * mat4x4[7] - mat4x4[9] * mat4x4[11];
	mat4x4_o[11] = -mat4x4[2] * mat4x4[3] - mat4x4[6] * mat4x4[7] - mat4x4[10] * mat4x4[11];

	mat4x4_o[12] = 0.0;
	mat4x4_o[13] = 0.0;
	mat4x4_o[14] = 0.0;
	mat4x4_o[15] = 1.0;
}


void kb::matRTto4x4(double* matR, double* matT, double* mat4x4)
{
	mat4x4[0] = matR[0];
	mat4x4[1] = matR[1];
	mat4x4[2] = matR[2];
	mat4x4[4] = matR[3];
	mat4x4[5] = matR[4];
	mat4x4[6] = matR[5];
	mat4x4[8] = matR[6];
	mat4x4[9] = matR[7];
	mat4x4[10] = matR[8];

	mat4x4[3] = matT[0];
	mat4x4[7] = matT[1];
	mat4x4[11] = matT[2];
	mat4x4[12] = 0;
	mat4x4[13] = 0;
	mat4x4[14] = 0;
	mat4x4[15] = 1;
}

void kb::mat4x4toRT(double* mat4x4, double* matR, double* matT)
{
	matR[0] = mat4x4[0];
	matR[1] = mat4x4[1];
	matR[2] = mat4x4[2];
	matR[3] = mat4x4[4];
	matR[4] = mat4x4[5];
	matR[5] = mat4x4[6];
	matR[6] = mat4x4[8];
	matR[7] = mat4x4[9];
	matR[8] = mat4x4[10];
	matT[0] = mat4x4[3];
	matT[1] = mat4x4[7];
	matT[2] = mat4x4[11];
}


double kb::dotproduct(double* v1, double* v2, int num)
{
	double sum = 0;
	for (int i = 0; i < num; i++) {
		sum += v1[i] * v2[i];
	}
	return sum;
}

void kb::crossproduct(double* p1, double* p2, double* p_out)
{
	p_out[0] = p1[1] * p2[2] - p1[2] * p2[1];
	p_out[1] = p1[2] * p2[0] - p1[0] * p2[2];
	p_out[2] = p1[0] * p2[1] - p1[1] * p2[0];
}

int kb::load_mat(const std::string& path, double* mat, int num)
{
	std::ifstream file(path.c_str());
	if (file.is_open() == false)
		return -1;

	std::string str1;
	for (int i = 0; i < num; i++) {
		file >> str1;
		mat[i] = std::stod(str1);
	}
	return 0;
}

void kb::save_mat(std::string& path, double* mat, int num)
{
	std::ofstream file(path.c_str());

	for (int i = 0; i < num; i++) {
		file << mat[i] << " ";
	}
}
void kb::save_mat(std::string& path, double* mat, int numColumn, int numRow)
{
	std::ofstream file(path.c_str());

	for (int j = 0; j < numRow; j++) {
		for (int i = 0; i < numColumn; i++) {
			file << mat[i + j * numColumn] << " ";
		}
		file << "\n";
	}
}


int kb::vec_unit(double* p1, double* p_out, int num)
{
	double sum = 0;
	for (int i = 0; i < num; i++) {
		sum += p1[i] * p1[i];
	}
	sum = sqrt(sum);
	if (sum < 1.0E-8) {
		return -1;
	}

	for (int i = 0; i < num; i++) {
		p_out[i] = p1[i] / sum;
	}
	return 0;
}

double kb::vec_length(double* mat1, int num)
{
	double sum = 0;
	for (int i = 0; i < num; i++) {
		sum += mat1[i] * mat1[i];
	}
	return sqrt(sum);
}

double kb::vec_length(double* mat1, double* mat2, int num)
{
	double sum = 0;
	for (int i = 0; i < num; i++) {
		double d = mat1[i] - mat2[i];
		sum += (d * d);
	}
	return sqrt(sum);
}

//	単位行列をセット
void kb::mat4x4_set1(double* mat1)
{
	mat1[0] = 1.0; mat1[1] = 0.0; mat1[2] = 0.0; mat1[3] = 0.0;
	mat1[4] = 0.0; mat1[5] = 1.0; mat1[6] = 0.0; mat1[7] = 0.0;
	mat1[8] = 0.0; mat1[9] = 0.0; mat1[10] = 1.0; mat1[11] = 0.0;
	mat1[12] = 0.0; mat1[13] = 0.0; mat1[14] = 0.0; mat1[15] = 1.0;
}

//	単位行列をセット
void kb::mat3x3_set1(double* mat1)
{
	mat1[0] = 1.0; mat1[1] = 0.0; mat1[2] = 0.0;
	mat1[3] = 0.0; mat1[4] = 1.0; mat1[5] = 0.0;
	mat1[6] = 0.0; mat1[7] = 0.0; mat1[8] = 1.0;
}

void kb::addWeighted(double* v1, double a1, double* v2, double a2, double* v3, int num)
{
	for (int i = 0; i < num; i++) {
		v3[i] = a1 * v1[i] + a2 * v2[i];
	}
}

void kb::copy(double* v1, double* v_out, int num)
{
	for (int i = 0; i < num; i++) {
		v_out[i] = v1[i];
	}
}

void kb::printf_mat4x4(double* mat1)
{
	printf("%.3f %.3f %.3f %.3f \n", mat1[0], mat1[1], mat1[2], mat1[3]);
	printf("%.3f %.3f %.3f %.3f \n", mat1[4], mat1[5], mat1[6], mat1[7]);
	printf("%.3f %.3f %.3f %.3f \n", mat1[8], mat1[9], mat1[10], mat1[11]);
	printf("%.3f %.3f %.3f %.3f \n", mat1[12], mat1[13], mat1[14], mat1[15]);
}

void kb::glmatset_t(double* mat1, double x, double y, double z)
{
	mat1[0] = 1.0; mat1[1] = 0.0; mat1[2] = 0.0; mat1[3] = 0.0;
	mat1[4] = 0.0; mat1[5] = 1.0; mat1[6] = 0.0; mat1[7] = 0.0;
	mat1[8] = 0.0; mat1[9] = 0.0; mat1[10] = 1.0; mat1[11] = 0.0;
	mat1[12] = x; mat1[13] = y; mat1[14] = z; mat1[15] = 1.0;
}


double kb::qtn_sign(double value)
{
	if (value >= 0.0) {
		return 1.0;
	}
	else {
		return -1.0;
	}
}

void kb::qtn_init(double* matQ)
{
	matQ[0] = 1.0;
	matQ[1] = 0.0;
	matQ[2] = 0.0;
	matQ[3] = 0.0;
}

void kb::qtn_R2Q(double* r, double* matQ)
{
	double q0 = (r[0] + r[4] + r[8] + 1.0) / 4.0;
	double q1 = (r[0] - r[4] - r[8] + 1.0) / 4.0;
	double q2 = (-r[0] + r[4] - r[8] + 1.0) / 4.0;
	double q3 = (-r[0] - r[4] + r[8] + 1.0) / 4.0;
	if (q0 < 0.0f) q0 = 0.0f;
	if (q1 < 0.0f) q1 = 0.0f;
	if (q2 < 0.0f) q2 = 0.0f;
	if (q3 < 0.0f) q3 = 0.0f;
	q0 = sqrt(q0);
	q1 = sqrt(q1);
	q2 = sqrt(q2);
	q3 = sqrt(q3);

	//	11(0) 12(1) 13(2)
	//	21(3) 22(4) 23(5)
	//	31(6) 32(7) 33(8)
	if (q0 >= q1 && q0 >= q2 && q0 >= q3) {
		q1 *= qtn_sign(r[7] - r[5]);
		q2 *= qtn_sign(r[2] - r[6]);
		q3 *= qtn_sign(r[3] - r[1]);
	}
	else if (q1 >= q0 && q1 >= q2 && q1 >= q3) {
		q0 *= qtn_sign(r[7] - r[5]);
		q2 *= qtn_sign(r[3] + r[1]);
		q3 *= qtn_sign(r[2] + r[6]);
	}
	else if (q2 >= q0 && q2 >= q1 && q2 >= q3) {
		q0 *= qtn_sign(r[2] - r[6]);
		q1 *= qtn_sign(r[3] + r[1]);
		q3 *= qtn_sign(r[7] + r[5]);
	}
	else if (q3 >= q0 && q3 >= q1 && q3 >= q2) {
		q0 *= qtn_sign(r[3] - r[1]);
		q1 *= qtn_sign(r[6] + r[2]);
		q2 *= qtn_sign(r[7] + r[5]);
	}
	else {
		printf("qtn_R2Q error\n");
		return;
	}
	double r0 = sqrt(q0*q0 + q1 * q1 + q2 * q2 + q3 * q3);
	matQ[0] = q0 / r0;
	matQ[1] = q1 / r0;
	matQ[2] = q2 / r0;
	matQ[3] = q3 / r0;
}

void kb::qtn_Q2R(double* q, double* r)
{
	double x2 = q[1] * q[1] * 2.0;
	double y2 = q[2] * q[2] * 2.0;
	double z2 = q[3] * q[3] * 2.0;
	double xy = q[1] * q[2] * 2.0;
	double yz = q[2] * q[3] * 2.0;
	double zx = q[3] * q[1] * 2.0;
	double xw = q[1] * q[0] * 2.0;
	double yw = q[2] * q[0] * 2.0;
	double zw = q[3] * q[0] * 2.0;

	r[0] = 1.0 - y2 - z2;
	r[1] = xy - zw;
	r[2] = zx + yw;

	r[3] = xy + zw;
	r[4] = 1.0 - z2 - x2;
	r[5] = yz - xw;

	r[6] = zx - yw;
	r[7] = yz + xw;
	r[8] = 1.0 - x2 - y2;
}

void kb::qtn_mul(double* p, double* q, double* pq)
{
	pq[0] = p[0] * q[0] - p[1] * q[1] - p[2] * q[2] - p[3] * q[3];
	pq[1] = p[0] * q[1] + p[1] * q[0] + p[2] * q[3] - p[3] * q[2];
	pq[2] = p[0] * q[2] - p[1] * q[3] + p[2] * q[0] + p[3] * q[1];
	pq[3] = p[0] * q[3] + p[1] * q[2] - p[2] * q[1] + p[3] * q[0];
}

void kb::qtn_dir2dq(double* dir_input, double deg_input, double* matQ)
{
	double deg_abs = deg_input;
	double dir1[3];
	if (deg_abs < 0.0) {
		deg_abs = -deg_abs;
		for (int i = 0; i < 3; i++) {
			dir1[i] = -dir_input[i];
		}
	}
	else {
		for (int i = 0; i < 3; i++) {
			dir1[i] = dir_input[i];
		}
	}

	double s = deg_abs / 360.0;
	//	double s=sqrt(dir[0]*dir[0]+dir[1]*dir[1]+dir[2]*dir[2]);
	double dir[3];
	kb::vec_unit(dir1, dir, 3);
	if (s < 10E-6) {
		matQ[0] = 1.0;
		matQ[1] = 0.0;
		matQ[2] = 0.0;
		matQ[3] = 0.0;
	}
	else {
		double sin_s = sin(s*M_PI);

		matQ[0] = cos(s*M_PI);
		matQ[1] = sin_s * dir[0];
		matQ[2] = sin_s * dir[1];
		matQ[3] = sin_s * dir[2];
	}
}

void kb::qtn_dir2dq_v2(double* dir_input, double deg_input, double* matQ)
{
	double s = deg_input / 360.0;
	double dir1[3];
	if (s < 0.0) {
		s = -s;
		for (int i = 0; i < 3; i++) {
			dir1[i] = -dir_input[i];
		}
	}
	else {
		for (int i = 0; i < 3; i++) {
			dir1[i] = dir_input[i];
		}
	}

	double sin_s = sin(s*M_PI);

	matQ[0] = cos(s*M_PI);
	matQ[1] = sin_s * dir1[0];
	matQ[2] = sin_s * dir1[1];
	matQ[3] = sin_s * dir1[2];
}

void kb::mat4x4CamOrg(double* mat4x4, double* org)
{
	org[0] = -mat4x4[0] * mat4x4[3] - mat4x4[4] * mat4x4[7] - mat4x4[8] * mat4x4[11];
	org[1] = -mat4x4[1] * mat4x4[3] - mat4x4[5] * mat4x4[7] - mat4x4[9] * mat4x4[11];
	org[2] = -mat4x4[2] * mat4x4[3] - mat4x4[6] * mat4x4[7] - mat4x4[10] * mat4x4[11];
}

void kb::glmat4x4CamOrg(double* mat4x4, double* org)
{
	org[0] = -mat4x4[0] * mat4x4[12] - mat4x4[1] * mat4x4[13] - mat4x4[2] * mat4x4[14];
	org[1] = -mat4x4[4] * mat4x4[12] - mat4x4[5] * mat4x4[13] - mat4x4[6] * mat4x4[14];
	org[2] = -mat4x4[8] * mat4x4[12] - mat4x4[9] * mat4x4[13] - mat4x4[10] * mat4x4[14];
}
void kb::vec_subtraction(double* v1, double* v2, double* v21, int num)
{
	for (int i = 0; i < num; i++) {
		v21[i] = v1[i] - v2[i];
	}
}
void kb::vec_plus(double* v1, double* v2, double* v21, int num)
{
	for (int i = 0; i < num; i++) {
		v21[i] = v1[i] + v2[i];
	}
}

double kb::frobenius_norm(double* mat1, double* mat2, int num)
{
	double sum = 0;
	for (int i = 0; i < num; i++) {
		double d = mat1[i] - mat2[i];
		sum += (d*d);
	}
	return sum;
}

double kb::frobenius_norm(double* mat1, int num)
{
	double sum = 0;
	for (int i = 0; i < num; i++) {
		sum += (mat1[i] * mat1[i]);
	}
	return sum;
}

void kb::gl_dir2rot(double* dir, double* pos, double* glmatRT)
{
	double matR[9];
	kb::dir2rot(dir, matR);

	glmatRT[0] = matR[0];	glmatRT[1] = matR[3];	glmatRT[2] = matR[6]; glmatRT[3] = 0.0;
	glmatRT[4] = matR[1];	glmatRT[5] = matR[4];	glmatRT[6] = matR[7]; glmatRT[7] = 0.0;
	glmatRT[8] = matR[2];	glmatRT[9] = matR[5];	glmatRT[10] = matR[8]; glmatRT[11] = 0.0;
	glmatRT[12] = pos[0];	glmatRT[13] = pos[1];	glmatRT[14] = pos[2];	glmatRT[15] = 1.0;
}

void kb::dir2rot(double* dir, double* matR)
{
	double c2 = dir[2];
	double s2 = sqrt(dir[0] * dir[0] + dir[1] * dir[1]);
	if (s2 < 1.0E-15) {
		matR[0] = 1.0; matR[1] = 0.0; matR[2] = 0.0;
		matR[3] = 1.0; matR[4] = 1.0; matR[5] = 0.0;
		matR[6] = 1.0; matR[7] = 0.0; matR[8] = 1.0;
		return;
	}

	double c1 = dir[0] / s2;
	double s1 = dir[1] / s2;

	matR[0] = c1 * c2; matR[1] = -s1; matR[2] = c1 * s2;
	matR[3] = s1 * c2; matR[4] = c1; matR[5] = s1 * s2;
	matR[6] = -s2; matR[7] = 0.0; matR[8] = c2;
}

//	任意軸まわりの回転行列
int kb::matR_rotVec(double matR[9], double dir[3], double radian)
{
	double matR1[9];	kb::mat3x3_set1(matR1);
	double udir[3];		kb::vec_unit(dir, udir, 3);
	double matR2[9];
	matR2[0] = 0.0;     matR2[1] = -udir[2]; matR2[2] = udir[1];
	matR2[3] = udir[2]; matR2[4] = 0.0;      matR2[5] = -udir[0];
	matR2[6] = -udir[1]; matR2[7] = udir[0]; matR2[8] = 0.0;

	double matR3[9];
	kb::matmul_3x3_3x3(matR2, matR2, matR3);

	double a = sin(radian);
	double b = 1.0 - cos(radian);
	for (int i = 0; i < 9; i++) {
		matR[i] = matR1[i] + a * matR2[i] + b * matR3[i];
	}
	return 0;
}

double kb::average(std::vector<double>& vec_val)
{
	int num1 = vec_val.size();

	double sum_val = 0;
	for (int i = 0; i < num1; i++) {
		sum_val += vec_val[i];
	}
	if (num1 > 0)
		return sum_val / (double)num1;
	return 0;
}

void kb::vec_multi(double* v1, double c1, int num)
{
	for (int i = 0; i < num; i++) {
		v1[i] = v1[i] * c1;
	}
}

int kb::vec_orthogonalTo3Vectors(
	double* v1,
	double* v2,
	double* v3,
	double* v_out
)
{
	double dp[3] = {
		kb::dotproduct(v1, v2, 3),
		kb::dotproduct(v2, v3, 3),
		kb::dotproduct(v3, v1, 3)
	};
	double vec_cp[3][3];
	kb::crossproduct(v1, v2, vec_cp[0]);
	kb::crossproduct(v2, v3, vec_cp[1]);
	kb::crossproduct(v3, v1, vec_cp[2]);

	for (int i = 0; i < 3; i++) {
		if (dp[i] < 0) { dp[i] = -dp[i]; }
	}

	//
	int max_i = 0;
	int max_dp = dp[0];
	for (int i = 1; i < 3; i++) {
		if (max_dp < dp[i]) { max_dp = dp[i]; }
	}

	if (max_i == 0) {
		double nvec_cp1[3];	kb::vec_unit(vec_cp[1], nvec_cp1, 3);
		double nvec_cp2[3];	kb::vec_unit(vec_cp[2], nvec_cp2, 3);
		double dp12 = kb::dotproduct(nvec_cp1, nvec_cp2, 3);
		if (dp12 < 0.0) {
			kb::vec_multi(nvec_cp2, -1.0, 3);
		}
		double nvec_avr[3];	kb::vec_plus(nvec_cp1, nvec_cp2, nvec_avr, 3);
		kb::vec_unit(nvec_avr, v_out, 3);
	}
	else if (max_i == 1) {
		double nvec_cp1[3];	kb::vec_unit(vec_cp[0], nvec_cp1, 3);
		double nvec_cp2[3];	kb::vec_unit(vec_cp[2], nvec_cp2, 3);
		double dp12 = kb::dotproduct(nvec_cp1, nvec_cp2, 3);
		if (dp12 < 0.0) {
			kb::vec_multi(nvec_cp2, -1.0, 3);
		}
		double nvec_avr[3];	kb::vec_plus(nvec_cp1, nvec_cp2, nvec_avr, 3);
		kb::vec_unit(nvec_avr, v_out, 3);
	}
	else if (max_i == 2) {
		double nvec_cp1[3];	kb::vec_unit(vec_cp[0], nvec_cp1, 3);
		double nvec_cp2[3];	kb::vec_unit(vec_cp[1], nvec_cp2, 3);
		double dp12 = kb::dotproduct(nvec_cp1, nvec_cp2, 3);
		if (dp12 < 0.0) {
			kb::vec_multi(nvec_cp2, -1.0, 3);
		}
		double nvec_avr[3];	kb::vec_plus(nvec_cp1, nvec_cp2, nvec_avr, 3);
		kb::vec_unit(nvec_avr, v_out, 3);
	}
	else {
		return -1;
	}
	return 0;
}

int kb::inverseMat2x2(double* m1, double* m2)
{
	double det = m1[0] * m1[3] - m1[1] * m1[2];
	if (-0.0000001 < det && det < 0.0000001)
		return -1;

	m2[0] = m1[3] / det;
	m2[1] = -m1[1] / det;
	m2[2] = -m1[2] / det;
	m2[3] = m1[0] / det;

	return 0;
}

//	転置操作
void kb::mattraspose_4x4(double* mat_i, double* mat_o)
{
	mat_o[0] = mat_i[0];  mat_o[1] = mat_i[4];  mat_o[2] = mat_i[8];  mat_o[3] = mat_i[12];
	mat_o[4] = mat_i[1];  mat_o[5] = mat_i[5];  mat_o[6] = mat_i[9];  mat_o[7] = mat_i[13];
	mat_o[8] = mat_i[2];  mat_o[9] = mat_i[6];  mat_o[10] = mat_i[10];  mat_o[11] = mat_i[14];
	mat_o[12] = mat_i[3];  mat_o[13] = mat_i[7];  mat_o[14] = mat_i[11];  mat_o[15] = mat_i[15];
}

void kb::mattraspose_3x3(double* mat_i, double* mat_o)
{
	mat_o[0] = mat_i[0];	mat_o[1] = mat_i[3];	mat_o[2] = mat_i[6];  
	mat_o[3] = mat_i[1];	mat_o[4] = mat_i[4];	mat_o[5] = mat_i[7]; 
	mat_o[6] = mat_i[2];	mat_o[7] = mat_i[5];	mat_o[8] = mat_i[8];	
}
