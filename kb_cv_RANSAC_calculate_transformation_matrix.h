#include <vector>

#include <opencv2/opencv.hpp>

#pragma once

namespace kb
{
	//	RANSACによる変換行列を計算する
	//		処理が成功すると０以上が出力される
	//		アフィン変換行列が計算できなかったとき、－1を返す。
	//
	//	  アフィン変換行列(2x3)を計算する
	//　	  r11 r12 t1
	//	　　  r21 r22 t2
	//		出力は3x3マトリックスとなる
	//
	//		透視投影変換行列も組み込んであるが、検証は十分にしていないので
	//		その手間がかかる
	int calculate_transformation_matrix_by_RANSAC(
		std::vector<cv::Point2f>& mp1,
		std::vector<cv::Point2f>& mp2,
		cv::Size& sz_img,			//	画像サイズ
		cv::Mat& matAf,				//	計算結果の3x3行列
		std::vector<cv::Point2f>& mp1_inlier,
		std::vector<cv::Point2f>& mp2_inlier,
		double threshold_dis1,					//	対応点一致するとみなす距離
		int thres_max_valid_cnt,				//	対応点一致する最小数
		int RANSAC_iter_num,					//	RANSAC試行回数
		int numThread,							//	マルチスレッド
		double det_min,							//	アフィン変換行列の2x2部分のdeterminant値の制限
		double det_max,							//	アフィン変換行列の2x2部分のdeterminant値の制限	
		double ratio_area,						//	画像の中心付近の対応点を優先的に使用するための係数
												//	　1.0 だとすべての点を均等に使用する
		double threshold_ratio_delta_center,	//	画像中心の移動距離を閾値設定(-1だと閾値の機能オフ)
		double threshold_angle,					//	回転角度の閾値(-1だと閾値の機能オフ)
		int mode								//    0: affine transfromation
												// else: perspective transformation
	);

	class CParam_calculate_transformation_matrix_by_RANSAC
	{
	public:
		CParam_calculate_transformation_matrix_by_RANSAC()
		{

		}
		double threshold_dis1;					//	対応点一致するとみなす距離
		int thres_max_valid_cnt;				//	対応点一致する最小数
		int RANSAC_iter_num;					//	RANSAC試行回数
		int numThread;							//	マルチスレッド
		double det_min;							//	アフィン変換行列の2x2部分のdeterminant値の制限
		double det_max;							//	アフィン変換行列の2x2部分のdeterminant値の制限	
		double ratio_area;						//	画像の中心付近の対応点を優先的に使用するための係数
												//	　1.0 だとすべての点を均等に使用する
		double threshold_ratio_delta_center;	//	画像中心の移動距離を閾値設定(-1だと閾値の機能オフ)
		double threshold_angle;					//	回転角度の閾値(-1だと閾値の機能オフ)
		int mode;								//    0: affine transfromation
												// else: perspective transformation

	};
};
