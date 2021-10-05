
#pragma once

namespace kb
{
	//	�ԁ`�΁`��
	void makeTemparaturePalette0(int tone_number, unsigned char* prr, unsigned char* pgg, unsigned char* pbb);

	//	�ԁ`�΁`�`��
	void makeTemparaturePalette(int tone_number, unsigned char* prr, unsigned char* pgg, unsigned char* pbb);
	//	���`�ԁ`�΁`�`��
	void makeTemparaturePalette2(int tone_number, unsigned char* prr, unsigned char* pgg, unsigned char* pbb);
	void makeTemparaturePalette3(int tone_number, unsigned char* prr, unsigned char* pgg, unsigned char* pbb);
	//	�ԁ`���`��
	void makeTemparaturePalette4(int tone_number, unsigned char* prr, unsigned char* pgg, unsigned char* pbb);

	//	�ԁ`���`�̃p���b�g
	void makeRedAndBluePalette(int tone_number, unsigned char* prr, unsigned char* pgg, unsigned char* pbb);
	//	�ԁ`���`�̃p���b�g
	void makeRedAndBluePalette2(int tone_number, unsigned char* prr, unsigned char* pgg, unsigned char* pbb);

	//	�����_���J���\�p���b�g�쐬
	void random_color_palette(int index, unsigned char* rr, unsigned char* gg, unsigned char* bb);
	//	�����_���J���\�p���b�g�쐬
	//		buffer number = 256
	void random_color_palette(unsigned char* rr, unsigned char* gg, unsigned char* bb);


};

