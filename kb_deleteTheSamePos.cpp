#include "kb_deleteTheSamePos.h"
#include <map>
#include "kb_box3.h"

int kb::deleteTheSamePosition(
	std::vector<float>& points,
	std::vector<float>& normals,
	std::vector<float>& points_red,
	std::vector<float>& normals_red,
	std::vector<int>& indices_red

)
{
	std::map< mist::vector3<float>, int > mapPositionCounter;
	int numPoints = points.size() / 3;
	int total_count = 0;
	std::vector<unsigned int> vecIndex;
	std::vector<mist::vector3<float>> vecPos;
	std::vector<mist::vector3<float>> vecNrm;

	for (int i = 0; i < numPoints; i++) {
		mist::vector3<float> p1(points[i * 3], points[i * 3 + 1], points[i * 3 + 2]);
		mist::vector3<float> n1(normals[i * 3], normals[i * 3 + 1], normals[i * 3 + 2]);
		std::map< mist::vector3<float>, int >::iterator ret1
			= mapPositionCounter.find(p1);
		if (ret1 == mapPositionCounter.end()) {
			mapPositionCounter[p1] = total_count;
			vecPos.push_back(p1);
			vecNrm.push_back(n1);
			vecIndex.push_back(total_count);

			total_count++;
		}
		else {
			int ii = mapPositionCounter[p1];
			vecIndex.push_back(ii);
			vecNrm[ii] += n1;
		}
	}

	int numNorm = vecNrm.size();
	for (int i = 0; i < numNorm; i++) {
		mist::vector3<float> n2 = vecNrm[i].unit();

		points_red.push_back(vecPos[i].x);
		points_red.push_back(vecPos[i].y);
		points_red.push_back(vecPos[i].z);
		normals_red.push_back(n2.x);
		normals_red.push_back(n2.y);
		normals_red.push_back(n2.z);
	}
	int numIndex = vecIndex.size();
	for (int i = 0; i < numIndex; i++) {
		indices_red.push_back(vecIndex[i]);
	}

	return 0;
}

int kb::deleteTheSamePosition(
	std::vector< mist::vector3< double > >& points,
	std::vector< mist::vector3< double > >& normals,
	std::vector<mist::vector3<double>>& vecPos,
	std::vector<mist::vector3<double>>& vecNrm,
	std::vector<int>& vecIndex
)
{
	std::map< mist::vector3<double>, int > mapPositionCounter;
	int numPoints = points.size();
	int total_count = 0;

	for (int i = 0; i < numPoints; i++) {
		std::map< mist::vector3<double>, int >::iterator ret1 = mapPositionCounter.find(points[i]);
		if (ret1 == mapPositionCounter.end()) {
			mapPositionCounter[points[i]] = total_count;
			vecPos.push_back(points[i]);
			vecNrm.push_back(normals[i / 3]);
			vecIndex.push_back(total_count);

			total_count++;
		}
		else {
			int ii = mapPositionCounter[points[i]];
			vecIndex.push_back(ii);
			vecNrm[ii] += normals[i / 3];
		}
	}

	return 0;
}


int kb::deleteTheSamePosition(
	std::vector<float>& p3d,
	std::vector<float>& points_red,
	std::vector<int>& face_n,
	float lenBox
)
{
	//double eps = 1.0E-10;
	//float eps=1.0E-10;
	//float eps=1.0E-8;
	float eps=1.0E-6;

	int num_pt = p3d.size() / 3;

	//
	//	lut[ output index ]=intput index
	//
	std::vector<int> lut;
	lut.resize(num_pt);
	for (int i = 0; i < num_pt; i++) {
		lut[i] = i;
	}

	//	box管理オブジェクト
	kb::Box3 box(1.0);
	box.create(p3d);

	//	同じ座標を持つものを探す
	for (int i = 0; i < num_pt; i++) {

		int ii = i * 3;
		double x1 = p3d[ii];
		double y1 = p3d[ii + 1];
		double z1 = p3d[ii + 2];

		if ((i % 100000) == 0) {
			std::cout << i << ": " << x1 << " " << y1 << " " << z1 << std::endl;
		}

		//__int64 idx=box.get(&(p3d[ii]));
		std::pair< Box3_IT, Box3_IT > range;
		box.get(&(p3d[ii]), range);

		for (Box3_IT it = range.first; it != range.second; it++) {

			int j = it->second;
			if (j <= i) {
				continue;
			}

			int jj = j * 3;

			double x = (double)p3d[jj] - x1;
			double y = (double)p3d[jj + 1] - y1;
			double z = (double)p3d[jj + 2] - z1;

			double d2 = x * x + y * y + z * z;
			if (d2 > eps)
				continue;

			//	LUTの更新
			int i2 = i;
			while (1) {
				if (i2 == lut[i2]) {
					break;
				}
				else {
					i2 = lut[i2];
				}
			}
			lut[j] = i2;

		}
	}


	//std::cout<<"find the same point: "<<num_pt<<std::endl;

	//	LUTの更新
	//	同じ座標を持つ場合、LUTで統一する
	//	上で行っているので、アルゴリズム上、必要ないかもしれない
	{
		int n = 0;
		for (int i = 0; i < num_pt; i++) {
			int i2 = lut[i];
			while (1) {
				if (i2 == lut[i2]) {
					break;
				}
				else {
					i2 = lut[i2];
					n++;
				}
			}
			lut[i] = i2;
		}
		std::cout << "update count: " << n << std::endl;
	}



	//	LUT内のインデックスを詰める
	int num_pt2 = 0;
	{
		std::multimap< int, int > lut2;
		for (int i = 0; i < num_pt; i++) {
			lut2.insert(std::pair<int, int>(lut[i], i));
		}

		int num_lut2 = lut2.size();

		{
			int ii = -1;
			std::multimap< int, int >::iterator it = lut2.begin();
			while (it != lut2.end()) {
				//std::cout<<i<<"/"<<num_lut2<<" "<<lut[it->second]<<" "<<it->first<<" "<<" "<<it->second<<" "<<lut2.count(it->first)<<std::endl;	

				if (it->first == ii) {
					//std::cout<<it->second<<" ";	
					lut[it->second] = num_pt2 - 1;
				}
				else {
					ii = it->first;
					//std::cout<<std::endl<<it->first<<": "<<it->second<<" ";	
					num_pt2++;

					lut[it->second] = num_pt2 - 1;
				}

				it++;
			}
		}
		//std::cout<<std::endl;
		std::cout << "node number: " << num_pt << " --> " << num_pt2 << std::endl;
	}

	//
	//	STL node number = num_pt
	//	STL face number = num_pt/3 or num_face
	//	B-reps node index = lut[ STL node index ]
	//	B-reps node number = num_pt2
	//

	//	重なっている座標を取り除く
	points_red.clear();
	points_red.resize(num_pt2 * 3);
	for (int i = 0; i < num_pt; i++) {
		int j = lut[i];

		points_red[j * 3] = p3d[i * 3];
		points_red[j * 3 + 1] = p3d[i * 3 + 1];
		points_red[j * 3 + 2] = p3d[i * 3 + 2];
	}

	face_n =lut;

	return 0;
}
