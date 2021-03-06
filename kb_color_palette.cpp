#include "kb_color_palette.h"



//	double hue = H;		//	色相、色調	0	--	360
//	double sat = S;		//	彩度、濃淡	0.0	--	1.0
//	double its = V;		//	明度、明暗	0.0	--  1.0
#define HSItoRGB(hue, sat, its, rr, gg, bb)\
	{\
		int its2=(int)(255.0*its+0.5);\
		if(0.0<sat && 0<its2 ){\
			double h1 = hue/60.0;	if( 6.0<=h1 ){ h1=0.0; }\
			int h2 = (int)h1;	double f1 = h1 - (double)h2; double f2 = 1.0-f1;\
			double p1 = its*(1.0 - sat);		\
			double q1 = its*(1.0 - sat*f1);		\
			double t1 = its*(1.0 - sat*f2);		\
			int p2 = (int)(255.0*p1+0.5);		\
			int q2 = (int)(255.0*q1+0.5);		\
			int t2 = (int)(255.0*t1+0.5);		\
			if(h2==0) {		rr=its2;gg=t2;bb=p2;	}	\
			else if(h2==1 ){ rr=q2;gg=its2;bb=p2;	}	\
			else if(h2==2 ){ rr=p2;gg=its2;bb=t2;	}	\
			else if(h2==3 ){ rr=p2;gg=q2;bb=its2;	}	\
			else if(h2==4 ){ rr=t2;gg=p2;bb=its2;	}	\
			else if(h2==5 ){ rr=its2;gg=p2;bb=q2;	}	\
		}else{									\
			rr=its2;gg=its2;bb=its2;			\
		}\
	}

void kb::makeTemparaturePalette4(int tone_number, unsigned char* prr, unsigned char* pgg, unsigned char* pbb)
{

	for (int i = 0; i < tone_number; i++) {
		double hue = 120.0 * (double)(tone_number - 1 - i) / (double)(tone_number - 1);

		unsigned char rr, gg, bb;
		HSItoRGB(hue, 1.0, 1.0, rr, gg, bb);

		prr[i] = rr;
		pgg[i] = gg;
		pbb[i] = bb;
	}
}

void kb::makeTemparaturePalette0(int tone_number, unsigned char* prr, unsigned char* pgg, unsigned char* pbb)
{

	for (int i = 0; i < tone_number; i++) {
		double hue = 240.0 * (double)(tone_number - 1 - i) / (double)(tone_number - 1);

		unsigned char rr, gg, bb;
		HSItoRGB(hue, 1.0, 1.0, rr, gg, bb);

		prr[i] = rr;
		pgg[i] = gg;
		pbb[i] = bb;
	}
}

void kb::makeTemparaturePalette(int tone_number, unsigned char* prr, unsigned char* pgg, unsigned char* pbb)
{

	for (int i = 0; i < tone_number; i++) {
		double hue = 300.0*(double)(tone_number - 1 - i) / (double)(tone_number - 1);

		unsigned char rr, gg, bb;
		if (0.0 <= hue && hue <= 240.0) {
			HSItoRGB(hue, 1.0, 1.0, rr, gg, bb);
		}
		else {
			HSItoRGB(240.0, 1.0, (300.0 - hue) / 60.0, rr, gg, bb);
		}

		prr[i] = rr;
		pgg[i] = gg;
		pbb[i] = bb;
	}
}

void kb::makeTemparaturePalette2(int tone_number, unsigned char* prr, unsigned char* pgg, unsigned char* pbb)
{

	for (int i = 0; i < tone_number; i++) {
		double h1 = 300.0*(double)(tone_number - 1 - i) / (double)(tone_number - 1);
		double hue = h1 - 30.0;

		unsigned char rr, gg, bb;
		if (hue < 0.0) {
			HSItoRGB(0.0, (30.0 + hue) / 30.0, 1.0, rr, gg, bb);
		}
		else if (0.0 <= hue && hue <= 240.0) {
			HSItoRGB(hue, 1.0, 1.0, rr, gg, bb);
		}
		else {
			HSItoRGB(240.0, 1.0, (270.0 - hue) / 30.0, rr, gg, bb);
		}

		prr[i] = rr;
		pgg[i] = gg;
		pbb[i] = bb;
	}
}

void kb::makeTemparaturePalette3(int tone_number, unsigned char* prr, unsigned char* pgg, unsigned char* pbb)
{

	for (int i = 0; i < tone_number; i++) {
		double h1 = 150.0*(double)(i) / (double)(tone_number - 1);
		double hue = h1 - 30.0;

		unsigned char rr, gg, bb;
		if (hue < 0.0) {
			double v1 = (30.0 + hue) / 30.0;
			HSItoRGB(240.0, 1.0, v1, rr, gg, bb);
		}
		else {
			double h2 = 240.0 + hue;
			HSItoRGB(h2, 1.0, 1.0, rr, gg, bb);
		}

		prr[i] = rr;
		pgg[i] = gg;
		pbb[i] = bb;
	}
}

void kb::makeRedAndBluePalette(int tone_number, unsigned char* prr, unsigned char* pgg, unsigned char* pbb)
{
	int half = tone_number / 2;
	for (int i = 0; i < half; i++) {
		int color = (int)(255.0*(double)(half - i) / (double)half);
		prr[i] = 0;
		pgg[i] = 0;
		pbb[i] = color;
	}
	for (int i = half; i < tone_number; i++) {
		int color = (int)(255.0*(double)(i - half) / (double)half);
		prr[i] = color;
		pgg[i] = 0;
		pbb[i] = 0;
	}
}

void kb::makeRedAndBluePalette2(int tone_number, unsigned char* prr, unsigned char* pgg, unsigned char* pbb)
{
	int half = tone_number / 2;
	for (int i = 0; i < half; i++) {
		int color = (int)(255.0*(double)(half - i) / (double)half);
		prr[i] = 255 - color;
		pgg[i] = 255 - color;
		pbb[i] = 255;
	}
	for (int i = half; i < tone_number; i++) {
		int color = (int)(255.0*(double)(i - half) / (double)half);
		prr[i] = 255;
		pgg[i] = 255 - color;
		pbb[i] = 255 - color;
	}
}



//	ランダムカラ―パレット作成
void kb::random_color_palette(int index, unsigned char* rr, unsigned char* gg, unsigned char* bb)
{
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

	if( index==0 ){	*rr=falseR[0];	*gg=falseG[0];	*bb=falseB[0];
	}else{
		int k2=index%255;
		if( k2<0 ){ k2+=255; }
		k2+=1;
		*rr=falseR[k2];	*gg=falseG[k2];	*bb=falseB[k2];
	}
}

//
void kb::random_color_palette(unsigned char* rr, unsigned char* gg, unsigned char* bb)
{
	unsigned char falseR[] = {
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
	unsigned char falseG[] = {
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
	unsigned char falseB[] = {
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

	for (int i = 0; i < 256; i++) {
		rr[i] = falseR[i];
		gg[i] = falseG[i];
		bb[i] = falseB[i];
	}
}

//
//void kb::dbl2string_vis(double val, double exponent10, std::string& str1)
//{
//	char buf[128];
//
//	if( exponent10>1.0 ){
//		sprintf_s(buf, 128, "%.0f", val);
//	}else if( exponent10>0.0 ){
//		sprintf_s(buf, 128, "%.1f", val);
//	}else if( exponent10>-1.0 ){
//		sprintf_s(buf, 128, "%.2f", val);
//	}else if( exponent10>-2.0 ){
//		sprintf_s(buf, 128, "%.3f", val);
//	}else if( exponent10>-3.0 ){
//		sprintf_s(buf, 128, "%.4f", val);
//	}else{
//		sprintf_s(buf, 128, "%f", val);
//	}
//	str1=buf;
//}
