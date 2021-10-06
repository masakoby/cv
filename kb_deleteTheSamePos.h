#include <vector>
#include <mist/vector.h>

#pragma once

namespace kb
{

	//	
	//	STL�t�@�C���`���ɂ����āA�אڂR�p�`�̍��W�l(x,y,z)���d�Ȃ��Ă���Ƃ�
	//	�������W�l����菜���A�R�p�`�̒��_�̂R���C���f�b�N�X�Ƃ��ĊǗ�����`����
	//	�ϊ�����֐�
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