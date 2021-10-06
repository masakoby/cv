
#pragma once


namespace kb
{
	inline void switchValue(int& a, int& b)
	{
		int c = a;
		a = b;
		b = c;
	}
};