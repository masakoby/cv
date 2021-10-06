#include "kb_cv_labeling.h"




int kb::visualize(
			cv::Mat& matL,
			cv::Mat& matV
			)
{
	cv::Size sz1=matL.size();
	matV=cv::Mat(sz1, CV_8UC3);

	unsigned char falseR[]={
		0x00, 0xbe, 0x6c, 0x52, 0xf1, 0xe9, 0xa6, 0x99, 0x47, 0x4d, 0xbb, 0x5a, 0xd4, 0x96, 0x89,
		0x9a, 0x78, 0xf6, 0x49, 0x4f, 0x66, 0xc4, 0xf6, 0xe1, 0xb0, 0xb9, 0x49, 0xc5, 0xe9, 0xea,
		0x53, 0xd6, 0x7e, 0x66, 0x57, 0xff, 0x61, 0x9d, 0x72, 0x84, 0x77, 0x53, 0x74, 0xd5, 0xd4,
		0x7e, 0xcc, 0x90, 0x8f, 0xd9, 0xf7, 0x87, 0x50, 0x8d, 0x82, 0xda, 0xce, 0x69, 0x6a, 0xd9,
		0xd4, 0x4a, 0x68, 0xbb, 0x88, 0x52, 0xe5, 0xd3, 0xf5, 0x59, 0x59, 0xc2, 0x68, 0x6a, 0xb1,
		0xc1, 0xa9, 0x8c, 0x95, 0xe1, 0xe9, 0xa7, 0xb5, 0x9a, 0xd1, 0xd1, 0xa1, 0x4e, 0xfe, 0x9f,
		0xe2, 0x47, 0x89, 0x79, 0x78, 0xb1, 0x6d, 0x96, 0x89, 0x6d, 0xa1, 0x41, 0x61, 0xe7, 0xdc,
		0x8d, 0xf2, 0xff, 0x75, 0x87, 0x4d, 0x82, 0xc2, 0x8c, 0x70, 0x54, 0xaa, 0xe6, 0xca, 0x9f,
		0x41, 0x4f, 0x72, 0xcd, 0x44, 0x66, 0xa1, 0xec, 0xe6, 0xad, 0xb0, 0xd8, 0xf4, 0x42, 0xc1,
		0x8c, 0xb8, 0x95, 0x5a, 0x99, 0x60, 0x80, 0xe9, 0xa5, 0xe4, 0xfe, 0x93, 0x73, 0x8a, 0xca,
		0xcf, 0x95, 0xbe, 0xad, 0x65, 0xc9, 0x4d, 0xc6, 0xc8, 0x88, 0x6b, 0xf9, 0xe7, 0x78, 0x99,
		0x74, 0xb8, 0x95, 0xdf, 0x6d, 0xd9, 0x65, 0x79, 0xeb, 0xe1, 0x6e, 0x5b, 0x8a, 0xf7, 0x4a,
		0x84, 0xb1, 0xee, 0x9e, 0x50, 0x81, 0xf6, 0x47, 0x48, 0xa4, 0x81, 0x98, 0x43, 0x57, 0x59,
		0x7f, 0x5f, 0x4e, 0xde, 0xb2, 0xbb, 0xe2, 0x7d, 0xd3, 0x6b, 0x83, 0xf9, 0xf0, 0x94, 0xaf,
		0xa4, 0x5e, 0x80, 0x6b, 0x7d, 0x72, 0x71, 0xb8, 0x4e, 0xbf, 0x74, 0xdc, 0xda, 0x81, 0x5c,
		0x49, 0xd2, 0xa9, 0xb9, 0xad, 0xb2, 0x5a, 0x77, 0xb5, 0x6c, 0x57, 0x9a, 0xb2, 0xe6, 0xbc,
		0x8d, 0xd6, 0x8d, 0x73, 0xcf, 0x45, 0xa8, 0xea, 0x4e, 0xd9, 0xed, 0xa0, 0xfa, 0x85, 0xb0,
		0xee	
	};
	unsigned char falseG[]={
		0x00, 0x84, 0xd6, 0x90, 0x01, 0xeb, 0xdb, 0x5e, 0xde, 0xc8, 0x8b, 0x7d, 0xcb, 0xf5, 0xdb,
		0x50, 0xfd, 0x9e, 0xdc, 0xf2, 0xd0, 0xb7, 0x91, 0x8b, 0xca, 0x72, 0x80, 0x99, 0x80, 0xc9,
		0xbf, 0xbf, 0xdc, 0x83, 0x49, 0x69, 0xcd, 0x9c, 0xe6, 0x4f, 0xd7, 0xcb, 0x9e, 0xd4, 0xa4,
		0xcf, 0xcf, 0x48, 0x75, 0xe5, 0x78, 0x44, 0xd4, 0xbe, 0x70, 0x64, 0xb1, 0xf8, 0x96, 0x67,
		0xf7, 0xd0, 0x76, 0xad, 0x79, 0xdb, 0xf4, 0xd8, 0xc5, 0x97, 0x76, 0xc9, 0xd4, 0x79, 0x6a,
		0x8c, 0x87, 0xf1, 0xc1, 0xc0, 0xa8, 0x86, 0x54, 0xe7, 0x55, 0xd9, 0x66, 0xe1, 0xd9, 0xe2,
		0x9b, 0x65, 0xa9, 0x7a, 0xc2, 0xdf, 0x62, 0xbf, 0x5e, 0xe3, 0xcb, 0x84, 0xc9, 0x8e, 0xf3,
		0xfe, 0xeb, 0xa0, 0x8c, 0x78, 0xd0, 0xbe, 0x46, 0xfa, 0xf0, 0x86, 0x5b, 0xfc, 0xbe, 0x89,
		0xfd, 0x68, 0x7b, 0xd3, 0xb4, 0x53, 0x5e, 0x4c, 0xb4, 0xcf, 0xca, 0x9d, 0x79, 0x7c, 0xf8,
		0x87, 0xa6, 0x4c, 0x8d, 0xe7, 0xde, 0xad, 0x67, 0xd5, 0x9f, 0x4c, 0xb3, 0x53, 0xaf, 0x6f,
		0xd3, 0xce, 0x65, 0xa1, 0xa6, 0xc0, 0x8f, 0xdb, 0xa6, 0x81, 0x68, 0x54, 0x71, 0x92, 0x72,
		0xfa, 0xb5, 0x57, 0x80, 0x8d, 0x8b, 0xa5, 0xbd, 0xb8, 0x60, 0x7b, 0x62, 0x8f, 0xe5, 0x9b,
		0xc6, 0xa7, 0x75, 0x6a, 0x9b, 0x43, 0xe9, 0xa1, 0x6c, 0x9e, 0xa3, 0xff, 0xcd, 0xc7, 0xbf,
		0x5d, 0xb9, 0x60, 0x98, 0xb6, 0xb8, 0x51, 0xd8, 0xbe, 0xd6, 0x98, 0xdc, 0xca, 0x92, 0x8d,
		0x90, 0x6a, 0x76, 0xb1, 0x5a, 0x82, 0xa8, 0x5e, 0xaf, 0xb0, 0x75, 0x58, 0xf2, 0xa0, 0xcb,
		0x74, 0xac, 0x5b, 0x88, 0xe1, 0x5d, 0xdc, 0x5d, 0x69, 0x93, 0xeb, 0xdf, 0xa2, 0xa4, 0x77,
		0xc3, 0xa9, 0xae, 0x60, 0x5d, 0x53, 0x59, 0xed, 0x80, 0xf8, 0xd5, 0x5c, 0x9f, 0x8e, 0x7d,
		0xb1
	};
	unsigned char falseB[]={
		0x00, 0xe1, 0xae, 0x49, 0xbb, 0xb3, 0x87, 0xb7, 0xb3, 0x43, 0xa6, 0x5d, 0xfc, 0x45, 0xae,
		0xee, 0x49, 0x7d, 0xad, 0x44, 0x6b, 0xa1, 0x9d, 0xda, 0x99, 0x9d, 0x7e, 0xd5, 0xb2, 0xcc,
		0x67, 0xd6, 0x8e, 0xef, 0x61, 0x8f, 0xd1, 0x72, 0xf0, 0x4a, 0xe8, 0xc9, 0xf4, 0x9f, 0x59,
		0xf4, 0xd3, 0xd3, 0xe6, 0xc0, 0x81, 0x5f, 0x61, 0x7b, 0x92, 0x54, 0x85, 0x46, 0x73, 0x68,
		0x4a, 0x57, 0xfa, 0xae, 0xfe, 0x43, 0x45, 0xce, 0x60, 0x8a, 0xd0, 0xcd, 0x49, 0x61, 0xa5,
		0xd6, 0x97, 0x9a, 0x9b, 0x7e, 0x9a, 0xc2, 0xbf, 0xd9, 0x90, 0x6c, 0x5e, 0x9c, 0x71, 0xa5,
		0xb4, 0x46, 0x82, 0x76, 0x63, 0xda, 0xe0, 0xa6, 0xf1, 0x6c, 0xc2, 0x65, 0xc5, 0x46, 0xa8,
		0xbe, 0x71, 0xd0, 0x7e, 0x73, 0xbe, 0xdb, 0x41, 0x7f, 0xa7, 0x95, 0x68, 0xf5, 0x7d, 0x8a,
		0xb8, 0xf6, 0x99, 0xf0, 0xa6, 0xcb, 0x4c, 0x73, 0xaa, 0xd5, 0xff, 0x4d, 0x59, 0x9c, 0xcd,
		0x64, 0x87, 0xb0, 0x4e, 0xb1, 0xb1, 0x41, 0x41, 0x9f, 0x42, 0xd1, 0x8f, 0x43, 0x7e, 0xd5,
		0xa1, 0x5a, 0xf6, 0xbe, 0xb4, 0x69, 0x56, 0x9d, 0xd8, 0x61, 0x62, 0xd0, 0x48, 0x86, 0xdb,
		0x4f, 0xb0, 0xf5, 0x6c, 0x74, 0x43, 0xf6, 0xf7, 0xe0, 0x8f, 0xf4, 0x8a, 0x5c, 0x87, 0x61,
		0xc3, 0x4a, 0x6f, 0xef, 0xc8, 0x8a, 0x9e, 0x81, 0xcd, 0xde, 0x8c, 0x9a, 0xcf, 0x50, 0xbd,
		0x89, 0x49, 0xe5, 0x42, 0xec, 0x73, 0x7e, 0x84, 0x50, 0x43, 0x8b, 0xbc, 0x6d, 0x74, 0xb5,
		0xd5, 0xfc, 0x4b, 0xdb, 0xea, 0x8d, 0x8c, 0xd9, 0xfa, 0x94, 0xe5, 0x46, 0x5b, 0x7f, 0xe9,
		0x55, 0xf7, 0xa3, 0x68, 0xd5, 0xe5, 0xe9, 0xeb, 0xc5, 0x98, 0x87, 0x68, 0xd5, 0xc6, 0x5f,
		0x8f, 0xd4, 0xbb, 0xca, 0xd6, 0xd7, 0xcc, 0x55, 0x84, 0xb8, 0x7a, 0x4e, 0xfc, 0x81, 0xbf,
		0xe4
	};


	for(int j=0;j<sz1.height;j++){
		for(int i=0;i<sz1.width;i++){
			int n=matL.at<int>(j,i);

			cv::Vec3b color(0,0,0);
			if( n>0 ){
				int n2=(n%255)+1;
				color[0]=falseR[n2];
				color[1]=falseG[n2];
				color[2]=falseB[n2];
			}
			matV.at<cv::Vec3b>(j,i)=color;
		}
	}
	return 0;
}


int kb::labeling_8n(
						cv::Mat& mat1,
						cv::Mat& matL,
						int	iDel
						)
{
	cv::Size sz1 = mat1.size();
	if (sz1.width == 0)
		return -1;

	unsigned int bcnt=sz1.width*sz1.height;


//	std::cout<<"kb::cvlabel::labeling_8n "<<sz1.width<<" "<< sz1.height<<std::endl;

	//	ラベリングバッファ
	std::vector<unsigned int> image;
	image.resize(bcnt, 0);


	//	ラベリングLUTテーブル
	std::vector<unsigned int> lutLabel;
	lutLabel.resize(bcnt+1);
	for(unsigned int i=0;i<=bcnt;i++){
		lutLabel[i]=i;
	}


	//	隣接数
	int neighbor=4;

	//	開始ラベル番号
	int current_label = 1;

	{
		for(int j=0;j<sz1.height;j++){
			for(int i=0;i<sz1.width;i++){
				if( mat1.at<unsigned char>(j,i)>0 ){

					//-----------------------
					//	隣接インデックス取得
					//	3 2 4
					//	1 0
					//-----------------------
					int ix[5]={ i+0, i-1, i+0, i-1,i+1 };
					int iy[5]={ j+0, j+0, j-1, j-1,j-1 };
					if( i==0 ){ ix[1] = -1; ix[3] = -1; }
					if( j==0 ){ iy[2] = -1; iy[3] = -1; iy[4] = -1; }
					if( i==sz1.width-1 ){ ix[4] = -1; }


					//-----------------------
					//	各評価値算出
					//		・輝度値
					//		・隣接ラベル番号
					//-----------------------
					unsigned int label[5]={0,0,0,0,0};
					{
						for(int ii=1;ii<=neighbor;ii++){
							if( ix[ii]>=0 && iy[ii]>=0 ){ label[ii] = image[ ix[ii]+iy[ii]*sz1.width ];	}
						}
					}

					//-----------------------
					//	連結判定
					//-----------------------
					int connect_flag = 0;
					unsigned char connect[5]={0,0,0,0,0};
					for(int ii=1;ii<=neighbor;ii++){
						if( ix[ii]>=0 && iy[ii]>=0 && 0<label[ii] ){
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
					if( connect_flag==0 ){
						image[ ix[0]+iy[0]*sz1.width ] = current_label;
						current_label++;
					}
					//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
					//
					//	連結が存在する時
					//	⇒一番小さいラベル番号をセットする
					//
					//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
					else if( 0<connect_flag ){
						//--------------------------------------------------------------------------------------------------
						//	隣接４点のラベル番号の中から最も小さい番号を見つける。（０以外の）
						//		・ラベル番号＞０
						//		・結合条件
						//--------------------------------------------------------------------------------------------------
						int current_lut[5]={0,0,0,0,0};
						int lutmin = current_label;
						{
							for(int ii=1;ii<=neighbor;ii++){
								if( connect[ii]==1 ){
									int current_ii=label[ii];
									while(1){
										int next_ii = lutLabel[current_ii];
										if( current_ii==next_ii ){
											current_lut[ii] = current_ii;
											break;
										}else{
											current_ii = next_ii;
										}
									}

									if( current_lut[ii]<lutmin ){
										lutmin = current_lut[ii];
									}
								}
							}
						}

						//--------------------------------------------------------------------------------------------------
						//	ルックアップテーブルの付け替え
						//--------------------------------------------------------------------------------------------------
						if( lutmin != current_label ){
							for(int ii=1;ii<=neighbor;ii++){
								if( connect[ii]==1 ){
									lutLabel[ current_lut[ii] ] = lutmin;
								}
							}
						}
						image[ ix[0]+iy[0]*sz1.width ] = lutmin;
					}
				}
			}
		}
	}


	//--------------------------------------------------------------------------------------------------
	//	ルックアップテーブルの付け替え
	//--------------------------------------------------------------------------------------------------
	{
		for(int ii=1;ii<current_label;ii++){
			//
			int current_ii=ii;
			while(1){
				int next_ii = lutLabel[current_ii];
				if( current_ii==next_ii ){
					lutLabel[ii] = current_ii;
					break;
				}else{
					current_ii = next_ii;
				}
			}
		}
	}

	//	ルックアップテーブルによるラベル画像の変換
	{
		for(int i=0;i<bcnt;i++){
			image[i] = lutLabel[image[i]];
		}
	}

	
	//	各ラベル番号のピクセル数（面積）を求める。
	std::vector<int> dataSquare; 
	{
		dataSquare.resize(current_label, 0);

		for(int i=0;i<bcnt;i++){
			dataSquare[ image[i] ]++;
		}
	}

	//	ラベル番号のソートをおこなうためのルックアップテーブルを作成する。
	//	各ラベル番号の面積に関してのしきい値判定を加味する。
	std::vector<int> lut; 
	int labelnum = 0;
	{
		lut.resize(current_label, 0);

		for(int i=1;i<current_label;i++){
			if( iDel<dataSquare[i] ){
				labelnum++;
				lut[i] = labelnum;
			}
		}
	}

	//	ラベル番号のソート
	matL=cv::Mat(sz1, CV_32SC1);
	{
		for(int i=0;i<bcnt;i++){
			int x=i%sz1.width;
			int y=i/sz1.width;

			matL.at<int>(y,x) = lut[ image[i] ];

		}
	}

	return labelnum;
}

int kb::labeling_8n(
	cv::Mat& mat1,
	cv::Mat& matL,
	int	iDel,
	std::vector<int>& squares,
	std::vector<cv::Point2f>& centers,
	std::vector<cv::Point>& vecPtsMin,
	std::vector<cv::Point>& vecPtsMax
)
{
	int labelnum = kb::labeling_8n(mat1, matL, iDel);

	cv::Size sz1 = mat1.size();

	if (labelnum > 0) {
		vecPtsMin.resize(labelnum, cv::Point(sz1.width - 1, sz1.height - 1));
		vecPtsMax.resize(labelnum, cv::Point(0, 0));
		squares.resize(labelnum, 0);
		std::vector<double> x_sum, y_sum;
		x_sum.resize(labelnum, 0);
		y_sum.resize(labelnum, 0);
		for (int j = 0; j < sz1.height; j++) {
			for (int i = 0; i < sz1.width; i++) {
				int lb = matL.at<int>(j, i);
				if (lb > 0) {
					if (i < vecPtsMin[lb - 1].x) { vecPtsMin[lb - 1].x = i; }
					if (j < vecPtsMin[lb - 1].y) { vecPtsMin[lb - 1].y = j; }
					if (vecPtsMax[lb - 1].x < i) { vecPtsMax[lb - 1].x = i; }
					if (vecPtsMax[lb - 1].y < j) { vecPtsMax[lb - 1].y = j; }
					squares[lb - 1]++;
					x_sum[lb - 1] += i;
					y_sum[lb - 1] += j;
				}
			}
		}

		centers.resize(labelnum, cv::Point2f(0, 0));
		for (int i = 0; i < labelnum; i++) {
			if (squares[i] > 0) {
				centers[i].x = x_sum[i] / (double)squares[i];
				centers[i].y = y_sum[i] / (double)squares[i];
			}
		}
	}

	return labelnum;
}

int kb::labeling_4n(
	cv::Mat& mat1,
	cv::Mat& matL,
	int	iDel,
	std::vector<int>& squares,
	std::vector<cv::Point2f>& centers,
	std::vector<cv::Point>& vecPtsMin,
	std::vector<cv::Point>& vecPtsMax
)
{
	int labelnum = kb::labeling_4n(mat1, matL, iDel);

	cv::Size sz1 = mat1.size();

	if (labelnum > 0) {
		vecPtsMin.resize(labelnum, cv::Point(sz1.width - 1, sz1.height - 1));
		vecPtsMax.resize(labelnum, cv::Point(0, 0));
		squares.resize(labelnum, 0);
		std::vector<double> x_sum, y_sum;
		x_sum.resize(labelnum, 0);
		y_sum.resize(labelnum, 0);
		for (int j = 0; j < sz1.height; j++) {
			for (int i = 0; i < sz1.width; i++) {
				int lb = matL.at<int>(j, i);
				if (lb > 0) {
					if (i < vecPtsMin[lb - 1].x) { vecPtsMin[lb - 1].x = i; }
					if (j < vecPtsMin[lb - 1].y) { vecPtsMin[lb - 1].y = j; }
					if (vecPtsMax[lb - 1].x < i) { vecPtsMax[lb - 1].x = i; }
					if (vecPtsMax[lb - 1].y < j) { vecPtsMax[lb - 1].y = j; }
					squares[lb - 1]++;
					x_sum[lb - 1] += i;
					y_sum[lb - 1] += j;
				}
			}
		}

		centers.resize(labelnum, cv::Point2f(0, 0));
		for (int i = 0; i < labelnum; i++) {
			if (squares[i] > 0) {
				centers[i].x = x_sum[i] / (double)squares[i];
				centers[i].y = y_sum[i] / (double)squares[i];
			}
		}
	}

	return labelnum;
}

int kb::labeling_4n(
	cv::Mat& mat1,
	cv::Mat& matL,
	int	iDel
)
{
	cv::Size sz1 = mat1.size();
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
	int neighbor = 2;

	//	開始ラベル番号
	int current_label = 1;

	{
		for (int j = 0; j < sz1.height; j++) {
			for (int i = 0; i < sz1.width; i++) {
				if (mat1.at<unsigned char>(j, i) > 0) {

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
							if (ix[ii] >= 0 && iy[ii] >= 0) { label[ii] = image[ix[ii] + iy[ii] * sz1.width]; }
						}
					}

					//-----------------------
					//	連結判定
					//-----------------------
					int connect_flag = 0;
					unsigned char connect[5] = { 0,0,0,0,0 };
					for (int ii = 1; ii <= neighbor; ii++) {
						if (ix[ii] >= 0 && iy[ii] >= 0 && 0 < label[ii]) {
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
	matL = cv::Mat(sz1, CV_32SC1);
	{
		for (int i = 0; i < bcnt; i++) {
			int x = i % sz1.width;
			int y = i / sz1.width;

			matL.at<int>(y, x) = lut[image[i]];

		}
	}


	return labelnum;
}


int kb::pickup_labeling_area(cv::Mat& matL, cv::Mat& mask8U, int label)
{
	cv::Size sz = matL.size();

	mask8U = cv::Mat(sz, CV_8UC1, cv::Scalar(0));

	if (label > 0) {
		for (int j = 0; j < sz.height; j++) {
			for (int i = 0; i < sz.width; i++) {
				if (matL.at<int>(j, i) == label) {
					mask8U.at<unsigned char>(j, i) = 255;
				}
			}
		}
	}
	else {
		for (int j = 0; j < sz.height; j++) {
			for (int i = 0; i < sz.width; i++) {
				if (matL.at<int>(j, i) > 0) {
					mask8U.at<unsigned char>(j, i) = 255;
				}
			}
		}
	}


	return 0;
}

void kb::updateLabelingLUT(std::vector<int>& lutLabel)
{
	int num = lutLabel.size();

	for (int ii = 1; ii < num; ii++) {
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
