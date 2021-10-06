
#pragma once

namespace kb
{
	//	あるベクトルに直交する２つのベクトルを取得する
	int orthogonalVectors(
		double vec_z[3], //入力z軸
		double vec_x[3], //出力x軸
		double vec_y[3]  //出力y軸
	);
	//	あるベクトル(z)に直交する２つのベクトル(x,y)を取得する。
	//	参照xベクトルに近いxベクトルを計算する
	int orthogonalVectors(
		double vec_z[3], //入力z軸
		double vec_x_near[3], //参照x軸
		double vec_x[3], //出力x軸
		double vec_y[3] //出力y軸
	);


	int orthogonalVectors(
		double vec_x0[3], //入力x1軸
		double vec_y0[3], //入力y1軸
		double vec_z0[3], //入力z1軸
		double vec_z1[3], //入力z2軸
		double vec_x1[3], //出力x2軸
		double vec_y1[3]  //出力y2軸
	);
	int orthogonalVectors(
		double vec_x0[3], //入力x1軸
		double vec_y0[3], //入力y1軸
		double vec_z0[3], //入力z1軸
		double vec_z1[3], //入力z2軸
		double vec_x1[3], //出力x2軸
		double vec_y1[3], //出力y2軸
		double thres_deg  // 最大角度
	);



};


