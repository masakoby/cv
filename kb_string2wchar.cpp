#include "kb_string.h"
//#include <iostream>
//#include <sstream>

//-----------------------------------------------------------------------------------
//	std::string --> unicode
void kb::string2wchar(std::string iStr, wchar_t* oBuf1, int cnt1)
{
	size_t wLen = 0;

	//ÉçÉPÅ[ÉãéwíË
	setlocale(LC_ALL, "japanese");
	//ïœä∑
	errno_t err = mbstowcs_s(&wLen, oBuf1, cnt1, iStr.c_str(), _TRUNCATE);

}

void kb::wchar2string(const wchar_t* oBuf1, std::string& oStr1) {
	size_t origsize = wcslen(oBuf1) + 1;

	const size_t newsize = 1000;
	size_t convertedChars = 0;
	char nstring[newsize];
	wcstombs_s(&convertedChars, nstring, origsize, oBuf1, _TRUNCATE);
	oStr1 = nstring;
}


