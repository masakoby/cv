#include <vector>

#pragma once

namespace kb
{
	//	�����_�̃}�b�`���O��RANSAC���s���ۂɎg�p����֐�
	//	�@number=5���ƃT�C�Y�T�̔z���p�ӂ���
	//�@	�@[*,*,*,*,*]
	//	�@�ő�l(max_num-1)�Ƃ��āA�l�ɂ��Ԃ�Ȃ��ŁA
	//	�@number�Ŏw�肵���T�C�Y�̔z����擾����֐�
	//
	//	�������͂ǂ����ŌĂ�ł��ǂ�
	//	srand( (unsigned)time( NULL ) );
	//
	int getRandomNumbers(
		int number, 
		int* buf,
		int max_num
	);

	std::vector<int> getRandomNumbers(int num);

};

//	�ȉ��̏�������̂ŁA�C���̕K�v�����肻�����B
//
// http://vivi.dyndns.org/tech/cpp/random.html
//����܂ōL���g�p����Ă��� rand() �ɂ�闐�������ɂ͈ȉ��̖��_������B
//���������͈͂�[0, 32767] �Ƌ���
//rand() % N �͈�l�ł͖���
//���������܂蒷���Ȃ�
//���������A���S���Y�����Œ�i�ʏ�͐��`�����@�j
//���K���z�ȂǁA��l�łȂ������������ʓ|
//rand() �Ő��������l�͈̔͂�[0, 32767] �Ƌ����B15�r�b�g�����Ȃ��B
//(rand() << 15) + rand() �Ƃ���΁A30�r�b�g�����ɂ��邱�Ƃ͉\�����A�X�}�[�g�ł͂Ȃ����A 
//�����A���S���Y���̊֌W�ŁA�����ɕ΂肪�o��ꍇ������B
//

