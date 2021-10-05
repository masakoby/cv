#pragma once

namespace kb
{
	inline double byte_swapping(double d)
	{
		double a;
		unsigned char* dst = (unsigned char*)&a;
		unsigned char* src = (unsigned char*)&d;

		dst[0] = src[7];
		dst[1] = src[6];
		dst[2] = src[5];
		dst[3] = src[4];
		dst[4] = src[3];
		dst[5] = src[2];
		dst[6] = src[1];
		dst[7] = src[0];

		return a;
	}

	inline int byte_swapping(int d)
	{
		int a;
		unsigned char* dst = (unsigned char*)&a;
		unsigned char* src = (unsigned char*)&d;

		dst[0] = src[3];
		dst[1] = src[2];
		dst[2] = src[1];
		dst[3] = src[0];

		return a;
	}



};
