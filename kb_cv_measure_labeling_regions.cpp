#include "kb_cv_measure_labeling_regions.h"
#include "kb_cv_labeling.h"
#include "kb_cv_relabeling.h"

int kb::measureSquare(
	cv::Mat& matL,
	int num,
	std::vector<int>& oVec
)
{
	cv::Size sz1 = matL.size();

	oVec.resize(num + 1, 0);

	for (int j = 0; j < sz1.height; j++) {
		for (int i = 0; i < sz1.width; i++) {
			int label = matL.at<int>(j, i);
			if (0 < label && label <= num) {
				oVec[label] += 1;
			}
		}
	}


	return 0;
}

int kb::measureBarycenter(
	cv::Mat& matLabel,
	int numLabel,
	std::vector<int>& vecSquare,
	std::vector<double>& vecPos
)
{
	cv::Size sz1 = matLabel.size();
	int numSquare = vecSquare.size();
	if (numSquare != (numLabel + 1))
		return -1;

	vecPos.resize((numLabel + 1) * 2, 0);

	for (int j = 0; j < sz1.height; j++) {
		for (int i = 0; i < sz1.width; i++) {
			int label = matLabel.at<int>(j, i);
			if (0 < label && label <= numLabel) {
				vecPos[label * 2] += i;
				vecPos[label * 2 + 1] += j;
			}
		}
	}

	for (int label = 1; label <= numLabel; label++) {
		if (vecSquare[label] > 0) {
			vecPos[label * 2] /= (double)vecSquare[label];
			vecPos[label * 2 + 1] /= (double)vecSquare[label];
		}
	}

	return 0;
}

int kb::measureAverage_RGB(
	cv::Mat& matLabel,
	int numLabel,
	cv::Mat& matRGB,
	std::vector<int>& vecSquare,
	std::vector<double>& vecAverage
)
{
	cv::Size sz1 = matLabel.size();

	cv::Size sz2 = matRGB.size();
	if (sz1 != sz2)
		return -1;

	vecSquare.resize(numLabel, 0);
	vecAverage.resize(numLabel * 3, 0);

	for (int j = 0; j < sz1.height; j++) {
		for (int i = 0; i < sz1.width; i++) {
			int label = matLabel.at<int>(j, i) - 1;
			if (0 <= label && label < numLabel) {
				cv::Vec3b a = matRGB.at<cv::Vec3b>(j, i);

				vecAverage[label * 3 + 0] += (double)a[0];
				vecAverage[label * 3 + 1] += (double)a[1];
				vecAverage[label * 3 + 2] += (double)a[2];
				vecSquare[label] += 1;
			}
		}
	}

	for (int k = 0; k < numLabel; k++) {
		if (vecSquare[k] == 0)
			continue;
		vecAverage[k * 3 + 0] = vecAverage[k * 3 + 0] / (double)vecSquare[k];
		vecAverage[k * 3 + 1] = vecAverage[k * 3 + 1] / (double)vecSquare[k];
		vecAverage[k * 3 + 2] = vecAverage[k * 3 + 2] / (double)vecSquare[k];
	}
	return 0;
}

int kb::measureAverageVariance_RGB(
	cv::Mat& matLabel,
	int numLabel,
	cv::Mat& matValueRGB,
	std::vector<int>& vecSquare,
	std::vector<double>& vecAverage,
	std::vector<double>& vecVariance
)
{
	cv::Size sz1 = matLabel.size();
	int numSquare = vecSquare.size();
	if (numSquare != (numLabel + 1))
		return -1;

	cv::Size sz2 = matValueRGB.size();
	if (sz1 != sz2)
		return -1;

	vecAverage.resize((numLabel + 1) * 3, 0);
	vecVariance.resize((numLabel + 1) * 3, 0);

	for (int j = 0; j < sz1.height; j++) {
		for (int i = 0; i < sz1.width; i++) {
			int label = matLabel.at<int>(j, i);
			if (0 < label && label <= numLabel) {
				cv::Vec3b a = matValueRGB.at<cv::Vec3b>(j, i);
				double a1 = (double)a[0];
				double a2 = (double)a[1];
				double a3 = (double)a[2];

				vecAverage[label * 3 + 0] += a1;
				vecAverage[label * 3 + 1] += a2;
				vecAverage[label * 3 + 2] += a3;
				vecVariance[label * 3 + 0] += (a1 * a1);
				vecVariance[label * 3 + 1] += (a2 * a2);
				vecVariance[label * 3 + 2] += (a3 * a3);
			}
		}
	}

	for (int label = 1; label <= numLabel; label++) {
		if (vecSquare[label] > 0) {
			vecAverage[label * 3 + 0] /= (double)vecSquare[label];
			vecAverage[label * 3 + 1] /= (double)vecSquare[label];
			vecAverage[label * 3 + 2] /= (double)vecSquare[label];
			vecVariance[label * 3 + 0] /= (double)vecSquare[label];
			vecVariance[label * 3 + 1] /= (double)vecSquare[label];
			vecVariance[label * 3 + 2] /= (double)vecSquare[label];

			vecVariance[label * 3 + 0] -= (vecAverage[label * 3 + 0] * vecAverage[label * 3 + 0]);
			vecVariance[label * 3 + 1] -= (vecAverage[label * 3 + 1] * vecAverage[label * 3 + 1]);
			vecVariance[label * 3 + 2] -= (vecAverage[label * 3 + 2] * vecAverage[label * 3 + 2]);
		}
	}

	return 0;
}


int kb::measureBoundingBox_by_PCA(
	cv::Mat& matL1, int num_label,
	std::vector<cv::Point2f>& v_pos,
	std::vector<cv::Point2f>& v_dir,
	std::vector<cv::Point2f>& v_pos2,
	std::vector<cv::Point2f>& v_pos4
)
{
	cv::Size sz = matL1.size();

	std::vector<int> v_sq;	v_sq.resize(num_label, 0);
	std::vector< std::vector<int> > vv_pos;	vv_pos.resize(num_label);

	for (int j = 0; j < sz.height; j++) {
		for (int i = 0; i < sz.width; i++) {
			int label = matL1.at<int>(j, i);
			if (label <= 0 || num_label < label)
				continue;

			v_sq[label - 1] += 1;

			vv_pos[label - 1].push_back(i);
			vv_pos[label - 1].push_back(j);
		}
	}

	v_pos.resize(num_label);
	v_dir.resize(num_label);
	v_pos2.resize(num_label * 2);
	v_pos4.resize(num_label * 4);

	for (int k = 0; k < num_label; k++) {
		int num_d = vv_pos[k].size() / 2;
		if (num_d <= 2)
			continue;

		double sum_x = 0, sum_y = 0;
		for (int i = 0; i < num_d; i++) {
			sum_x += vv_pos[k][i * 2];
			sum_y += vv_pos[k][i * 2 + 1];
		}

		//	重心位置
		sum_x /= (double)num_d;
		sum_y /= (double)num_d;

		cv::Mat data(num_d, 2, CV_64F);
		for (int i = 0; i < num_d; i++) {
			data.at<double>(i, 0) = (double)vv_pos[k][i * 2] - sum_x;
			data.at<double>(i, 1) = (double)vv_pos[k][i * 2 + 1] - sum_y;
		}

		cv::Mat mean(1, 2, CV_64F, cv::Scalar(0.0));
		cv::PCA pca(data, mean, cv::PCA::Flags::DATA_AS_ROW, 2);

		for (int i = 0; i < 2; i++) {
			std::cout << k << ": " << pca.eigenvalues.at<double>(i) << ", "
				<< pca.eigenvectors.at<double>(i, 0) << " " << pca.eigenvectors.at<double>(i, 1) << std::endl;
		}

		double dv[2] = { pca.eigenvectors.at<double>(0,0), pca.eigenvectors.at<double>(0,1) };
		cv::Point2f p[2];
		double max_dp = 0, min_dp = 0;
		for (int i = 0; i < num_d; i++) {
			double dx = (double)vv_pos[k][i * 2] - sum_x;
			double dy = (double)vv_pos[k][i * 2 + 1] - sum_y;
			double dp = dx * dv[0] + dy * dv[1];
			if (max_dp < dp) {
				p[0].x = sum_x + dv[0] * dp;
				p[0].y = sum_y + dv[1] * dp;
				max_dp = dp;
			}
			if (dp < min_dp) {
				p[1].x = sum_x + dv[0] * dp;
				p[1].y = sum_y + dv[1] * dp;
				min_dp = dp;
			}
		}

		//double max_dp2[2] = { 0,0 }, min_dp2[2] = { 0,0 };
		double max_dp2[2] = { 0,0 };
		cv::Point2f p4[4];
		for (int i = 0; i < num_d; i++) {
			double dx = (double)vv_pos[k][i * 2] - sum_x;
			double dy = (double)vv_pos[k][i * 2 + 1] - sum_y;
			//double dp = dx * dv[0] + dy * dv[1];
			double dcp = dx * dv[1] - dy * dv[0];
			if (dcp > 0.0) {
				if (max_dp2[0] < dcp) {
					max_dp2[0] = dcp;
				}
			}
			else {
				if (max_dp2[1] > dcp) {
					max_dp2[1] = dcp;
				}
			}
			//double abs_dcp = sqrt(fabs(dcp));
			//double dp_dcp = fabs(dp * abs_dcp);
			//if (dp < 0.0) {
			//	dp_dcp = -dp_dcp;
			//}
			//if (dcp > 0.0) {
			//	if (max_dp2[0] < dp_dcp) {
			//		p4[0].x = vv_pos[k][i * 2];
			//		p4[0].y = vv_pos[k][i * 2 + 1];
			//		max_dp2[0] = dp_dcp;
			//	}
			//}
			//else {
			//	if (max_dp2[1] < dp_dcp) {
			//		p4[1].x = vv_pos[k][i * 2];
			//		p4[1].y = vv_pos[k][i * 2 + 1];
			//		max_dp2[1] = dp_dcp;
			//	}
			//}
			//if (dcp > 0.0) {
			//	if (dp_dcp < min_dp2[0]) {
			//		p4[2].x = vv_pos[k][i * 2];
			//		p4[2].y = vv_pos[k][i * 2 + 1];
			//		min_dp2[0] = dp_dcp;
			//	}
			//}
			//else {
			//	if (dp_dcp < min_dp2[1]) {
			//		p4[3].x = vv_pos[k][i * 2];
			//		p4[3].y = vv_pos[k][i * 2 + 1];
			//		min_dp2[1] = dp_dcp;
			//	}
			//}
		}
		{
			p4[0].x = p[0].x + dv[1] * max_dp2[0];
			p4[0].y = p[0].y - dv[0] * max_dp2[0];
			p4[1].x = p[0].x + dv[1] * max_dp2[1];
			p4[1].y = p[0].y - dv[0] * max_dp2[1];

			p4[2].x = p[1].x + dv[1] * max_dp2[1];
			p4[2].y = p[1].y - dv[0] * max_dp2[1];
			p4[3].x = p[1].x + dv[1] * max_dp2[0];
			p4[3].y = p[1].y - dv[0] * max_dp2[0];
		}


		v_pos[k].x = sum_x;
		v_pos[k].y = sum_y;
		v_pos2[k * 2] = p[0];
		v_pos2[k * 2 + 1] = p[1];
		v_pos4[k * 4] = p4[0];
		v_pos4[k * 4 + 1] = p4[1];
		v_pos4[k * 4 + 2] = p4[2];
		v_pos4[k * 4 + 3] = p4[3];
	}


	return 0;
}

//	ラベル領域ごとの３次元ヒストグラム取得
int kb::measureHistogram3D_RGB(
	cv::Mat& matLabel,
	int numLabel,
	cv::Mat& matRGB,
	int num_bin,//histogramのビン数
	std::vector<float>& hist
)
{
	if (num_bin < 2 || num_bin>256)
		return -1;
	cv::Size sz = matLabel.size();
	cv::Size sz2 = matRGB.size();
	if (sz != sz2)
		return -1;

	int num_buf = num_bin * num_bin * num_bin * numLabel;
	hist.resize(num_buf, 0.0);
	std::vector<int> vcnt;
	vcnt.resize(numLabel, 0);

	int step = 256 / num_bin;
	int m1 = 256 % num_bin;
	if (m1 > 0) {
		step++;
	}
	int num_bin2 = num_bin * num_bin;
	int num_bin3 = num_bin * num_bin * num_bin;

	for (int j = 0; j < sz.height; j++) {
		for (int i = 0; i < sz.width; i++) {
			int label = matLabel.at<int>(j, i);
			if (label <= 0 || numLabel < label)
				continue;
			cv::Vec3b b = matRGB.at<cv::Vec3b>(j, i);

			int x = b[0] / step;
			int y = b[1] / step;
			int z = b[2] / step;
			int idx = x + y * num_bin + z * num_bin2 + num_bin3 * (label - 1);

			hist[idx]++;
			vcnt[label-1]++;
		}
	}

	for (int k = 0; k < numLabel; k++) {
		if (vcnt[k] == 0)
			continue;
		for (int i = 0; i < num_bin3; i++) {
			hist[i + num_bin3 * k]= hist[i + num_bin3 * k]/(float)vcnt[k];
		}
	}


	return 0;
}

//
int kb::measureBoundingBox(
	cv::Mat& matL1, int labelnum,
	std::vector<int>& squares,
	std::vector<cv::Point>& vecPtsMin,
	std::vector<cv::Point>& vecPtsMax
)
{
	cv::Size sz1 = matL1.size();

	vecPtsMin.resize(labelnum, cv::Point(sz1.width - 1, sz1.height - 1));
	vecPtsMax.resize(labelnum, cv::Point(0, 0));
	squares.resize(labelnum, 0);

	for (int j = 0; j < sz1.height; j++) {
		for (int i = 0; i < sz1.width; i++) {
			int lb = matL1.at<int>(j, i);
			if (lb > 0) {
				if (i < vecPtsMin[lb - 1].x) { vecPtsMin[lb - 1].x = i; }
				if (j < vecPtsMin[lb - 1].y) { vecPtsMin[lb - 1].y = j; }
				if (vecPtsMax[lb - 1].x < i) { vecPtsMax[lb - 1].x = i; }
				if (vecPtsMax[lb - 1].y < j) { vecPtsMax[lb - 1].y = j; }
				squares[lb - 1]++;
			}
		}
	}
	for (int k = 0; k < labelnum; k++) {
		if (squares[k]>0)
			continue;
		vecPtsMin[k] = cv::Point(-1, -1);
		vecPtsMax[k] = cv::Point(-1, -1);
	}
	return 0;
}


int kb::measureMinimumDistance(
	cv::Mat& matL,
	int numLabel,
	std::vector<float>& oVec
)
{
	cv::Size sz1 = matL.size();

	//	ラベル領域のエッジ領域を取り出す
	//		以前の関数名　labeling_edge
	cv::Mat matL2;
	kb::extract_edge_32S( matL, matL2);


	std::vector < std::vector<cv::Point>> vvPts;
	vvPts.resize(numLabel);
	for (int j = 0; j < sz1.height; j++) {
		for (int i = 0; i < sz1.width; i++) {
			int label = matL2.at<int>(j, i);
			if (label <= 0 || numLabel<label)
				continue;
			vvPts[label - 1].push_back(cv::Point(i, j));
		}
	}
	oVec.resize(numLabel * numLabel, -1);

	for (int k1 = 0; k1 < numLabel; k1++) {
		int num1 = vvPts[k1].size();
		for (int k2 = k1+1; k2 < numLabel; k2++) {
			int num2 = vvPts[k2].size();
			int d2_min = sz1.width * sz1.height;
			for (int i1 = 0; i1 < num1; i1+=2) {
				for (int i2 = 0; i2 < num2; i2+=2) {
					cv::Point p= vvPts[k1][i1] - vvPts[k2][i2];
					int d2 = p.x * p.x + p.y * p.y;
					if (d2 < d2_min) {
						d2_min = d2;
					}
				}
			}
			oVec[k1 + k2 * numLabel] = d2_min;
			oVec[k2 + k1 * numLabel] = d2_min;
		}
	}
	return 0;
}

int kb::measureContours(
	cv::Mat& matL,
	int numLabel,
	std::vector<std::vector<std::vector<cv::Point>>>& vv_contours
)
{
	cv::Size sz1 = matL.size();


	vv_contours.resize(numLabel);
	for (int label = 1; label <= numLabel; label++) {
		cv::Mat mat1(sz1, CV_8U, cv::Scalar(0));

		for (int j = 0; j < sz1.height; j++) {
			for (int i = 0; i < sz1.width; i++) {
				if (label != matL.at<int>(j, i))
					continue;
				mat1.at<unsigned char>(j, i) = 255;
			}
		}

		std::vector< std::vector<cv::Point> > contours;
		std::vector<cv::Vec4i> hierarchy;
		cv::findContours(mat1, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

		vv_contours[label - 1] = contours;
	}


	return 0;
}
