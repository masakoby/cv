
#include <string>

#pragma once

namespace kb
{
	//-----------------------------------------------------------------------------------
	//	std::string --> unicode
	void string2wchar(std::string iStr, wchar_t* oBuf1, int cnt1);
	//	unicode --> std::string
	void wchar2string(const wchar_t* oBuf1, std::string& oStr1);

};

