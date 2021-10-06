#include "kb_cv_relabeling.h"
#include "kb_cv_labeling.h"
#include "kb_cv_measure_labeling_regions.h"

int kb::relabeling_4n(
	cv::Mat& matL1,
	int num_label1,
	cv::Mat& matL2,
	int del
)
{
	cv::Size sz = matL1.size();
	matL2 = cv::Mat(sz, CV_32SC1, cv::Scalar(0));

	int num_label2 = 0;
	for (int k = 1; k <= num_label1; k++) {
		cv::Mat mat1(sz, CV_8UC1);
		for (int j = 0; j < sz.height; j++) {
			for (int i = 0; i < sz.width; i++) {
				if (matL1.at<int>(j, i) == k) {
					mat1.at<unsigned char>(j, i) = 255;
				}
				else {
					mat1.at<unsigned char>(j, i) = 0;
				}
			}
		}

		cv::Mat matL;
		std::vector<int> squares;
		std::vector<cv::Point2f> centers;
		std::vector<cv::Point> vecPtsMin, vecPtsMax;
		int num1 = kb::labeling_4n(mat1, matL, del, squares, centers, vecPtsMin, vecPtsMax);

		for (int j = 0; j < sz.height; j++) {
			for (int i = 0; i < sz.width; i++) {
				if (matL1.at<int>(j, i) == k) {
					matL2.at<int>(j, i) = matL.at<int>(j, i) + num_label2;
				}
			}
		}
		num_label2 += num1;
	}
	return num_label2;
}

int kb::relabeling_8n(
	cv::Mat& matL1,
	cv::Mat& matL2,
	int iDel
)
{
	cv::Size sz1 = matL1.size();
	if (sz1.width == 0)
		return -1;

	int bcnt = sz1.width * sz1.height;

	//	ラベリングバッファ
	std::vector<int> image;
	image.resize(bcnt, 0);


	//	ラベリングLUTテーブル
	std::vector< int> lutLabel;
	lutLabel.resize(bcnt + 1);
	for (int i = 0; i <= bcnt; i++) {
		lutLabel[i] = i;
	}

	//	隣接数
	int neighbor = 4;

	//	開始ラベル番号
	int current_label = 1;

	{
		for (int j = 0; j < sz1.height; j++) {
			for (int i = 0; i < sz1.width; i++) {
				if (matL1.at<int>(j, i) > 0) {

					//-----------------------
					//	隣接インデックス取得
					//	3 2 4
					//	1 0
					//-----------------------
					int ix[5] = { i + 0, i - 1, i + 0, i - 1,i + 1 };
					int iy[5] = { j + 0, j + 0, j - 1, j - 1,j - 1 };
					if (i == 0) { ix[1] = -1; ix[3] = -1; }
					if (j == 0) { iy[2] = -1; iy[3] = -1; iy[4] = -1; }
					if (i == sz1.width - 1) { ix[4] = -1; }


					//-----------------------
					//	各評価値算出
					//		・輝度値
					//		・隣接ラベル番号
					//-----------------------
					int label[5] = { 0,0,0,0,0 };
					{
						for (int ii = 1; ii <= neighbor; ii++) {
							if (ix[ii] >= 0 && iy[ii] >= 0) {
								label[ii] = image[ix[ii] + iy[ii] * sz1.width];
							}
						}
					}
					int label2[5] = { 0,0,0,0,0 };
					{
						for (int ii = 0; ii <= neighbor; ii++) {
							if (ix[ii] >= 0 && iy[ii] >= 0) {
								label2[ii] = matL1.at<int>(iy[ii], ix[ii]);
							}
						}
					}

					//-----------------------
					//	連結判定
					//-----------------------
					int connect_flag = 0;
					unsigned char connect[5] = { 0,0,0,0,0 };
					for (int ii = 1; ii <= neighbor; ii++) {
						if (ix[ii] >= 0 && iy[ii] >= 0 && label2[0] == label2[ii]) {
							connect[ii] = 1;
							connect_flag++;
						}
					}

					//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
					//
					//	連結が存在しない時
					//	⇒新しいラベル番号をセットする
					//
					//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
					if (connect_flag == 0) {
						image[ix[0] + iy[0] * sz1.width] = current_label;
						current_label++;
					}
					//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
					//
					//	連結が存在する時
					//	⇒一番小さいラベル番号をセットする
					//
					//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
					else if (0 < connect_flag) {
						//--------------------------------------------------------------------------------------------------
						//	隣接４点のラベル番号の中から最も小さい番号を見つける。（０以外の）
						//		・ラベル番号＞０
						//		・結合条件
						//--------------------------------------------------------------------------------------------------
						int current_lut[5] = { 0,0,0,0,0 };
						int lutmin = current_label;
						{
							for (int ii = 1; ii <= neighbor; ii++) {
								if (connect[ii] == 1) {
									int current_ii = label[ii];
									while (1) {
										int next_ii = lutLabel[current_ii];
										if (current_ii == next_ii) {
											current_lut[ii] = current_ii;
											break;
										}
										else {
											current_ii = next_ii;
										}
									}

									if (current_lut[ii] < lutmin) {
										lutmin = current_lut[ii];
									}
								}
							}
						}

						//--------------------------------------------------------------------------------------------------
						//	ルックアップテーブルの付け替え
						//--------------------------------------------------------------------------------------------------
						if (lutmin != current_label) {
							for (int ii = 1; ii <= neighbor; ii++) {
								if (connect[ii] == 1) {
									lutLabel[current_lut[ii]] = lutmin;
								}
							}
						}
						image[ix[0] + iy[0] * sz1.width] = lutmin;
					}
				}
			}
		}
	}


	//--------------------------------------------------------------------------------------------------
	//	ルックアップテーブルの付け替え
	//--------------------------------------------------------------------------------------------------
//	printf("debug1 %d\n", current_label);
	{
		for (int ii = 1; ii < current_label; ii++) {
			//
			int current_ii = ii;
			while (1) {
				int next_ii = lutLabel[current_ii];
				if (current_ii == next_ii) {
					lutLabel[ii] = current_ii;
					break;
				}
				else {
					current_ii = next_ii;
				}
			}
		}
	}

	//	ルックアップテーブルによるラベル画像の変換
	{
		for (int i = 0; i < bcnt; i++) {
			image[i] = lutLabel[image[i]];
		}
	}


	//	各ラベル番号のピクセル数（面積）を求める。
	std::vector<int> dataSquare;
	{
		dataSquare.resize(current_label, 0);

		for (int i = 0; i < bcnt; i++) {
			dataSquare[image[i]]++;
		}
	}

	//	ラベル番号のソートをおこなうためのルックアップテーブルを作成する。
	//	各ラベル番号の面積に関してのしきい値判定を加味する。
	std::vector<int> lut;
	int labelnum = 0;
	{
		lut.resize(current_label, 0);

		for (int i = 1; i < current_label; i++) {
			if (iDel < dataSquare[i]) {
				labelnum++;
				lut[i] = labelnum;
			}
		}
	}

	//	ラベル番号のソート
	matL2 = cv::Mat(sz1, CV_32SC1);
	{
		for (int i = 0; i < bcnt; i++) {
			int x = i % sz1.width;
			int y = i / sz1.width;

			matL2.at<int>(y, x) = lut[image[i]];

		}
	}


	return labelnum;
}

int kb::relabeling_distance_between_regions(
	cv::Mat& matL1,
	int num_label1,
	cv::Mat& matL2,
	int dis1
)
{
	float thres_dis2 = dis1 * dis1;
	std::vector<float> v_dis;
	kb::measureMinimumDistance(matL1, num_label1, v_dis);

	std::vector<int> lut;
	lut.resize(num_label1);
	for (int i = 0; i < num_label1; i++) {
		lut[i] = i;
	}

	for (int i1 = 0; i1 < num_label1; i1++) {
		for (int i2 = i1 + 1; i2 < num_label1; i2++) {
			if (v_dis[i1 + i2 * num_label1] > thres_dis2)
				continue;
			lut[i2] = i1;
			updateLabelingLUT(lut);
		}
	}

	cv::Mat matL1a;
	matL1.copyTo(matL1a);
	cv::Size sz1 = matL1.size();
	for (int j = 0; j < sz1.height; j++) {
		for (int i = 0; i < sz1.width; i++) {
			int label = matL1.at<int>(j, i);
			if (label <= 0)
				continue;
			matL1a.at<int>(j, i) = lut[label - 1]+1;
		}
	}

	//cv::Mat matL2_vis;
	//kb::visualize(matL1a, matL2_vis);
	//cv::namedWindow("2v", cv::WINDOW_NORMAL);
	//cv::imshow("2v", matL2_vis);


	return kb::relabeling_close_it_up(matL1a, matL2);
}

int kb::relabeling_close_it_up(cv::Mat& matL1, cv::Mat& matL2)
{
	cv::Size sz = matL1.size();

	matL2 = cv::Mat(sz, CV_32SC1, cv::Scalar(0));
	std::set<int> s1;

	for (int j = 0; j < sz.height; j++) {
		for (int i = 0; i < sz.width; i++) {
			int label = matL1.at<int>(j, i);
			if (label <= 0)
				continue;

			s1.insert(label);
		}
	}

	int num = s1.size();
	//for(int i=0;i<num;i++){
	//	std::cout<<s1[i]<<std::endl;
	//}

	std::map<int, int> lut;

	std::set<int>::iterator it = s1.begin();
	std::set<int>::iterator it_end = s1.end();

	int num_label = 0;
	while (it != it_end) {
		//std::cout<<*it<<std::endl;

		num_label++;
		lut[*it] = num_label;

		it++;
	}

	for (int j = 0; j < sz.height; j++) {
		for (int i = 0; i < sz.width; i++) {
			int label = matL1.at<int>(j, i);
			if (label <= 0)
				continue;

			matL2.at<int>(j, i) = lut[label];
		}
	}

	return num_label;
}

int kb::dilate_32S(
	cv::Mat& matL1,
	int num_label,
	cv::Mat& matL2,
	int num_max_iter,
	cv::Mat& mask0
)
{
	cv::Size sz = matL1.size();

	cv::Mat mask;
	{
		cv::Size sz2 = mask0.size();
		if (sz == sz2) {
			mask = mask0;
		}
		else {
			mask = cv::Mat(sz, CV_8U, cv::Scalar(255));
		}
	}

	matL1.copyTo(matL2);


	int d[8][2] = {
		1,0,
		-1,0,
		0,1,
		0,-1,
		1,1,
		1,-1,
		-1,1,
		-1,-1
	};

	int iter = 0;
	while (1) {
		cv::Mat matL3;
		matL2.copyTo(matL3);

		int cnt = 0;
		for (int j = 1; j < sz.height - 1; j++) {
			for (int i = 1; i < sz.width - 1; i++) {
				if (matL2.at<int>(j, i) != 0)
					continue;
				if (mask.at<unsigned char>(j, i) == 0)
					continue;

				int label[8];
				int num1 = 0;
				for (int ii = 0; ii < 4; ii++) {
					label[ii] = matL2.at<int>(j + d[ii][1], i + d[ii][0]);
					if (label[ii] > 0) {
						num1++;
					}
				}
				if (num1 == 0)
					continue;

				int idx = 0;
				int label2[8];
				int num_label2[4] = { 0,0,0,0 };
				for (int ii = 0; ii < 4; ii++) {
					if (label[ii] == 0)
						continue;

					int flag = 0;
					for (int jj = 0; jj < idx; jj++) {
						if (label[ii] == label2[jj]) {
							num_label2[jj] += 1;
							flag = 1;
						}
					}
					if (flag == 0) {
						label2[idx] = label[ii];
						num_label2[idx] = 1;
						idx++;
					}
				}
				if (idx == 0)
					continue;

				//
				int jj_max = -1;
				int num_max = 0;
				for (int jj = 0; jj < idx; jj++) {
					if (num_max < num_label2[jj]) {
						num_max = num_label2[jj];
						jj_max = label2[jj];
					}
				}

				if (jj_max < 0)
					continue;


				matL3.at<int>(j, i) = jj_max;
				cnt++;
			}
		}
		matL3.copyTo(matL2);


		if (cnt == 0)
			break;

		iter++;
		std::cout << iter << ": " << cnt << std::endl;

		if (num_max_iter > 0 && num_max_iter <= iter)
			break;

	}
	return 0;
}

//	ラベル領域のエッジ領域を取り出す
int kb::extract_edge_32S(cv::Mat& matL, cv::Mat& matL_out)
{
	if (matL.empty() == true)
		return -1;

	int d[4][2] = { 1,0, -1,0, 0,1, 0,-1 };
	cv::Size sz = matL.size();

	matL_out = cv::Mat(sz, CV_32SC1, cv::Scalar(0));
	for (int j = 0; j < sz.height; j++) {
		for (int i = 0; i < sz.width; i++) {
			int label = matL.at<int>(j, i);
			if (label == 0)
				continue;

			int edge_flag = 0;
			for (int ii = 0; ii < 4; ii++) {
				int x = i + d[ii][0];
				int y = j + d[ii][1];
				if (x < 0 || sz.width <= x || y < 0 || sz.height <= y) {
					edge_flag = 1;
					break;
				}
				if (matL.at<int>(y, x) != label) {
					edge_flag = 1;
					break;
				}
			}

			if (edge_flag > 0) {
				matL_out.at<int>(j, i) = label;
			}
		}
	}

	return 0;
}
