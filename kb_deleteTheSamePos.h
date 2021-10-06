#include <vector>
#include <mist/vector.h>

#pragma once

namespace kb
{

	//	
	//	STLファイル形式において、隣接３角形の座標値(x,y,z)が重なっているとき
	//	同じ座標値を取り除き、３角形の頂点の３つをインデックスとして管理する形式へ
	//	変換する関数
	//
	int deleteTheSamePosition(
		std::vector<float>& points,
		std::vector<float>& normals,
		std::vector<float>& points_red,
		std::vector<float>& normals_red,
		std::vector<int>& indices_red
	);

	int deleteTheSamePosition(
		std::vector< mist::vector3< double > >& points,
		std::vector< mist::vector3< double > >& normals,
		std::vector<mist::vector3<double>>& vecPos,
		std::vector<mist::vector3<double>>& vecNrm,
		std::vector<int>& vecIndex
	);


	//	
	int deleteTheSamePosition(
		std::vector<float>& p3d,
		std::vector<float>& points_red,
		std::vector<int>& indices_red,
		float lenBox = 1.0
	);

};