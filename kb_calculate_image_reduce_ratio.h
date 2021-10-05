#pragma once


namespace kb
{
	//	��̉摜�T�C�Y�i�摜�̏c�������͉��̃s�N�Z�����j�ɏ]���āA�摜���k������{�����v�Z����
	//	�k���̕K�v���Ȃ���΁A�[�P��Ԃ��B
	inline double calculate_image_reduce_ratio(int width_reduced, int width, int height)
	{
		float w1 = sqrt((float)width * (float)height);
		float w2 = width_reduced;
		if (w2 < w1) {
			return (w2 / w1);
		}
		else {
			return -1.0;
		}
	}
};