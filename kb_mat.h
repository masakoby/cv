#include <string>
#include <vector>

#pragma once

namespace kb
{
	//	3x3回転行列
	void matRotX(double* mat3x3, double deg);
	void matRotY(double* mat3x3, double deg);
	void matRotZ(double* mat3x3, double deg);

	//	行列演算
	void matmul_3x3_3x1(double* mat1, double* vec1, double* vec2);
	void matmul_3x3_3x3(double* mat1, double* mat2, double* mat3);
	void matmul_1x3_3x3(double* vec1, double* mat1, double* vec2);

	//	4x4行列と縦ベクトルの掛け算
	void matmul_4x4_4x1(const double* mat1, const double* vec1, double* vec2);
	//	横ベクトルと4x4行列の掛け算
	void matmul_1x4_4x4(double* vec1, double* mat1, double* vec2);
	//	4x4行列の掛け算
	void matmul_4x4_4x4(double* mat1, double* mat2, double* mat3);


	//	4x4 RT行列
	//	逆行列
	void mat4x4inverse(double* mat4x4, double* mat4x4_o);
	//	
	void matRTto4x4(double* matR, double* matT, double* mat4x4);
	//	
	void mat4x4toRT(double* mat4x4, double* matR, double* matT);

	//	転置操作
	void mattraspose_4x4(double* mat_in, double* mat_out);
	void mattraspose_3x3(double* mat_in, double* mat_out);


	void mat4x4CamOrg(double* mat4x4, double* org);
	void glmat4x4CamOrg(double* mat4x4, double* org);

	//	任意軸まわりの回転行列を取得する
	int matR_rotVec(double matR[9], double dir[3], double radian);


	//	ｎ次元ベクトルの内積
	double dotproduct(double* p1, double* p2, int num);
	//	３次元ベクトルの外積
	void crossproduct(double* p1, double* p2, double* p_out);

	//	ベクトル正規化（長さ１）を行う
	int vec_unit(double* p1, double* p_out, int num);

	//	ベクトル長さを取得
	double vec_length(double* mat1, int num);
	double vec_length(double* mat1, double* mat2, int num);


	//	配列コピー
	void copy(double* v1, double* v_out, int num);

	//	引き算
	void vec_subtraction(double* v1, double* v2, double* v21, int num);
	//	足し算
	void vec_plus(double* v1, double* v2, double* v21, int num);

	//	フロベニウスノルム
	double frobenius_norm(double* mat1, int num);
	double frobenius_norm(double* mat1, double* mat2, int num);

	//	平均
	double average(std::vector<double>& vec_val);

	//３分岐における分岐面の法線ベクトルを計算する
	int vec_orthogonalTo3Vectors(
		double* v1,
		double* v2,
		double* v3,
		double* v_out
	);
	//
	void vec_multi(double* v1, double c1, int num);


	//	並進成分に値をセットする
	void glmatset_t(double* mat1, double x, double y, double z);


	//	ベクトルの重み付き和
	void addWeighted(double* v1, double a1, double* v2, double a2, double* v3, int num);


	//	単位行列をセットする
	void mat3x3_set1(double* mat);
	//	単位行列をセットする
	void mat4x4_set1(double* mat);


	//	スペース区切りのテキスト行列ファイル読み込み
	int load_mat(const std::string& path, double* mat, int num);
	void save_mat(std::string& path, double* mat, int num);
	void save_mat(std::string& path, double* mat, int numColumn, int numRow);

	//
	void printf_mat4x4(double* mat1);


	//	quaternion
	void qtn_init(double* matQ);
	//	R : 3x3, Q : 1x4
	void qtn_R2Q(double* matR, double* matQ);
	void qtn_Q2R(double* matQ, double* matR);
	//	基本的に左から掛ける
	void qtn_mul(double* matQ1, double* matQ2, double* matQ12);
	double qtn_sign(double value);
	void qtn_dir2dq(double* dir, double deg, double* matQ);
	void qtn_dq2dir(double* matQ, double* dir, double * deg);
	void qtn_dir2dq_v2(double* dir_input, double deg_input, double* matQ);


	void dir2rot(double* dir, double* matR);
	void gl_dir2rot(double* dir, double* pos, double* matR);
	

	int inverseMat2x2(double* m1, double* m2);

};
