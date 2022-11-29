#include "kb_cv_arrange_cvmat.h"
#include "kb_cv_resize.h"

void kb::arrange_mat2(cv::Mat& mat1, cv::Mat& mat2, cv::Mat& matV)
{
	cv::Size sz1 = mat1.size();
	cv::Size sz2 = mat2.size();

	if (sz1.width <= 0 || sz2.width <= 0)
		return;

	cv::Size sz3 = sz1;

	sz3.width += sz2.width;
	if (sz3.height < sz2.height) { sz3.height = sz2.height; }

	matV = cv::Mat(sz3, CV_8UC3);
	mat1.copyTo(matV(cv::Rect(0, 0, sz1.width, sz1.height)));
	mat2.copyTo(matV(cv::Rect(sz1.width, 0, sz2.width, sz2.height)));
}


void kb::arrange_matN_subset(std::vector<cv::Mat>& vec_mat, cv::Mat& matV, int num_width, int start_idx, int num_mat)
{
	int num = vec_mat.size();
	if (num <= 0 || start_idx<0 || num<=start_idx)
		return;

	int num_end = start_idx + num_mat;
	if (num < num_end) {
		num_end = num;
	}

	std::vector<cv::Mat> vec_mat2;
	vec_mat2.resize(num_mat);
	for (int k = 0; k < num_mat; k++) {
		if ((start_idx+k) >= num)
			break;
		vec_mat2[k] = vec_mat[start_idx + k];
	}
	kb::arrange_matN(vec_mat2, matV, num_width);

}

void kb::arrange_matN(std::vector<cv::Mat>& vec_mat, cv::Mat& matV, int num_width)
{
	int num = vec_mat.size();
	if (num <= 0)
		return;

	cv::Size sz = vec_mat[0].size();
	if (sz.width <= 0 || sz.height <= 0)
		return;

	//　縦横に配置する画像数を設定する
	int nx = num, ny = 1;
	if (num_width <= 0) {
		for (int d = 1; d <= num; d++) {
			int n1 = num / d;
			int a1 = num % d;

			if (a1 > 0) {
				n1++;
			}

			int n2 = d;

			int w = sz.width * n1;
			int h = sz.height * n2;
			if (w < h) {
				nx = n1;
				ny = n2;
				break;
			}
		}

		int det_y = num % nx;
		ny = num / nx;
		if (det_y > 0) {
			ny++;
		}
	}
	else {
		nx = num_width;
		int det_y = num % nx;
		ny = num / nx;
		if (det_y > 0) {
			ny++;
		}
	}


	cv::Size sz2(nx * sz.width, ny * sz.height);

	int kk = 0;
	cv::Mat matOv(sz2, CV_8UC3);
	for (int k = 0; k < num; k++) {
		if (vec_mat[k].empty() == true)
			continue;

		cv::Mat mat3;
		int dp = vec_mat[k].depth();
		int ch = vec_mat[k].channels();
		if (ch == 1) {
			cv::cvtColor(vec_mat[k], mat3, cv::COLOR_GRAY2BGR);
		}
		else {
			mat3 = vec_mat[k];
		}
		cv::Size sz3 = mat3.size();

		cv::Mat mat4;
		if (sz != sz3) {
			cv::resize(mat3, mat4, sz, 0.0, 0.0, cv::INTER_CUBIC);
		}
		else {
			mat4 = mat3;
		}


		int ii = kk % nx;
		int jj = kk / nx;
		int x0 = ii * sz2.width / nx;
		int y0 = jj * sz2.height / ny;

		mat3.copyTo(matOv(cv::Rect(x0, y0, sz.width, sz.height)));
		kk++;
	}
	matV = matOv;
}

//	異なる画像サイズの配列に対して、タイリングして１枚の大きな画像にする関数
int kb::arrange_matN(
	std::vector<cv::Mat>& vec_mat,
	cv::Mat& matV,
	int nx, int ny, int width_tile)
{
	int num = vec_mat.size();
	if (num <= 0)
		return -1;

	int max_num = nx * ny;

	cv::Size sz(nx * width_tile, ny * width_tile);
	matV = cv::Mat(sz, CV_8UC3, cv::Scalar(255, 255, 255));
	for (int k = 0; k < num; k++) {
		if (k >= max_num)
			break;

		cv::Size sz1 = vec_mat[k].size();
		if (sz1.width == 0 || sz1.height == 0)
			continue;

		cv::Size sz2;
		if (sz1.width >= sz1.height) {
			sz2.width = width_tile;
			sz2.height = width_tile * sz1.height / sz1.width;
		}
		else {
			sz2.width = width_tile * sz1.width / sz1.height;
			sz2.height = width_tile;
		}

		cv::Mat mat2;
		kb::resize(vec_mat[k], mat2, sz2);

		int x0 = (k % nx) * width_tile;
		int y0 = (k / nx) * width_tile;

		mat2.copyTo(matV(cv::Rect(x0, y0, sz2.width, sz2.height)));
	}

	return 0;
}
