
#pragma once

namespace kb
{
	//	����x�N�g���ɒ�������Q�̃x�N�g�����擾����
	int orthogonalVectors(
		double vec_z[3], //����z��
		double vec_x[3], //�o��x��
		double vec_y[3]  //�o��y��
	);
	//	����x�N�g��(z)�ɒ�������Q�̃x�N�g��(x,y)���擾����B
	//	�Q��x�x�N�g���ɋ߂�x�x�N�g�����v�Z����
	int orthogonalVectors(
		double vec_z[3], //����z��
		double vec_x_near[3], //�Q��x��
		double vec_x[3], //�o��x��
		double vec_y[3] //�o��y��
	);


	int orthogonalVectors(
		double vec_x0[3], //����x1��
		double vec_y0[3], //����y1��
		double vec_z0[3], //����z1��
		double vec_z1[3], //����z2��
		double vec_x1[3], //�o��x2��
		double vec_y1[3]  //�o��y2��
	);
	int orthogonalVectors(
		double vec_x0[3], //����x1��
		double vec_y0[3], //����y1��
		double vec_z0[3], //����z1��
		double vec_z1[3], //����z2��
		double vec_x1[3], //�o��x2��
		double vec_y1[3], //�o��y2��
		double thres_deg  // �ő�p�x
	);



};


