#include "kb_inifile.h"
#include <sstream>

#if 0
#include <Windows.h>

//	INI file 形式のファイルから浮動小数データを読み取る
int kb::read(const char* iPath, const char* iSection, const char* iKey, double& oValue)
{
	char cstr1[4096];
	int rtn = GetPrivateProfileStringA(iSection, iKey, "", cstr1, 4096, iPath);
	if (rtn > 0) {
		oValue = atof(cstr1);
	}
	return rtn;
}
int kb::read(const char* iPath, const char* iSection, const char* iKey, float& oValue)
{
	char cstr1[4096];
	int rtn = GetPrivateProfileStringA(iSection, iKey, "", cstr1, 4096, iPath);
	if (rtn > 0) {
		oValue = atof(cstr1);
	}
	return rtn;
}

int kb::read(const char* iPath, const char* iSection, const char* iKey, std::string& oValue)
{
	char cstr1[4096];
	int rtn = GetPrivateProfileStringA(iSection, iKey, "", cstr1, 4096, iPath);
	if (rtn > 0) {
		oValue = cstr1;
	}
	return rtn;
}

int kb::write(const char* iPath, const char* iSection, const char* iKey, std::string& iValue)
{
	int rtn = WritePrivateProfileStringA(iSection, iKey, iValue.c_str(), iPath);

	return rtn;
}
int kb::write(const char* iPath, const char* iSection, const char* iKey, const char* iValue)
{
	return WritePrivateProfileStringA(iSection, iKey, iValue, iPath);
}


int kb::read(const char* iPath, const char* iSection, const char* iKey, int& oValue)
{
	char cstr1[4096];
	int rtn = GetPrivateProfileStringA(iSection, iKey, "", cstr1, 4096, iPath);
	if (rtn > 0) {
		oValue = atoi(cstr1);
	}
	return rtn;
}

//	INI file 形式のファイルから浮動小数データを読み取る
int kb::read_csv(const char* iPath, const char* iSection, const char* iKey, double* oValue, int num)
{
	char cstr1[4096];
	int rtn = GetPrivateProfileStringA(iSection, iKey, "", cstr1, 4096, iPath);



	if (rtn > 0) {
		std::istringstream stream(cstr1);

		//1行のうち、文字列とコンマを分割する
		for (int k = 0; k < num; k++) {
			std::string token;
			std::getline(stream, token, ',');
			size_t n1 = token.length();
			if (n1 == 0) {
			}
			else {
				oValue[k] = std::stod(token);
			}
			if (stream.eof() != false)
				break;
		}
	}


	return rtn;
}

//	INI file 形式のファイルから浮動小数データを読み取る
int kb::read_space(const char* iPath, const char* iSection, const char* iKey, double* oValue, int num)
{
	char cstr1[4096];
	int rtn = GetPrivateProfileStringA(iSection, iKey, "", cstr1, 4096, iPath);

	if (rtn > 0) {
		std::stringstream sstream1(cstr1);
		std::string str2;
		for (int i = 0; i < num; i++) {
			sstream1 >> str2;
			oValue[i] = atof(str2.c_str());
		}
	}

	return rtn;
}


//	INI file 形式のファイルから浮動小数データを読み取る
int kb::write_csv(const char* iPath, const char* iSection, const char* iKey, double* iValue, int num)
{
	std::stringstream sstream1;

	for (int i = 0; i < num; i++) {
		sstream1 << iValue[i];
		if (i == (num - 1)) {
			break;
		}
		sstream1 << ",";
	}

	std::string str1 = sstream1.str();
	int rtn = WritePrivateProfileStringA(iSection, iKey, str1.c_str(), iPath);

	return rtn;
}
//	INI file 形式のファイルから浮動小数データを読み取る
int kb::write_space(const char* iPath, const char* iSection, const char* iKey, double* iValue, int num)
{
	std::stringstream sstream1;

	for (int i = 0; i < num; i++) {
		sstream1 << iValue[i];
		if (i == (num - 1)) {
			break;
		}
		sstream1 << " ";
	}

	std::string str1 = sstream1.str();
	int rtn = WritePrivateProfileStringA(iSection, iKey, str1.c_str(), iPath);

	return rtn;
}

//	INI file 形式のファイルから浮動小数データを読み取る
int kb::write(const char* iPath, const char* iSection, const char* iKey, double iValue)
{
	std::stringstream sstream1;

	sstream1 << iValue;

	std::string str1 = sstream1.str();
	//::OutputDebugStringA(str1.c_str());
	int rtn = WritePrivateProfileStringA(iSection, iKey, str1.c_str(), iPath);

	return rtn;
}
//	INI file 形式のファイルから浮動小数データを読み取る
int kb::write(const char* iPath, const char* iSection, const char* iKey, int iValue)
{
	std::stringstream sstream1;

	sstream1 << iValue;

	std::string str1 = sstream1.str();
	//::OutputDebugStringA(str1.c_str());
	int rtn = WritePrivateProfileStringA(iSection, iKey, str1.c_str(), iPath);

	return rtn;
}


//	INI file 形式のファイルから浮動小数データを読み取る
int kb::read_csv(const char* iPath, const char* iSection, const char* iKey, int* oValue, int num)
{
	char cstr1[4096];
	int rtn = GetPrivateProfileStringA(iSection, iKey, "", cstr1, 4096, iPath);

	if (rtn > 0) {
		std::istringstream stream(cstr1);

		//1行のうち、文字列とコンマを分割する
		for (int k = 0; k < num; k++) {
			std::string token;
			std::getline(stream, token, ',');
			size_t n1 = token.length();
			if (n1 == 0) {
			}
			else {
				oValue[k] = std::stod(token);
			}
			if (stream.eof() != false)
				break;
		}
	}


	return rtn;
}

//	INI file 形式のファイルから浮動小数データを読み取る
int kb::read_space(const char* iPath, const char* iSection, const char* iKey, int* oValue, int num)
{
	char cstr1[4096];
	int rtn = GetPrivateProfileStringA(iSection, iKey, "", cstr1, 4096, iPath);

	if (rtn > 0) {
		std::stringstream sstream1(cstr1);
		std::string str2;
		for (int i = 0; i < num; i++) {
			sstream1 >> str2;
			oValue[i] = atoi(str2.c_str());
		}
	}

	return rtn;
}


//	INI file 形式のファイルから浮動小数データを読み取る
int kb::write_csv(const char* iPath, const char* iSection, const char* iKey, int* iValue, int num)
{
	std::stringstream sstream1;

	for (int i = 0; i < num; i++) {
		sstream1 << iValue[i];
		if (i == (num - 1)) {
			break;
		}
		sstream1 << ",";
	}

	std::string str1 = sstream1.str();
	//::OutputDebugStringA(str1.c_str());
	int rtn = WritePrivateProfileStringA(iSection, iKey, str1.c_str(), iPath);

	return rtn;
}

int kb::write_space(const char* iPath, const char* iSection, const char* iKey, int* iValue, int num)
{
	std::stringstream sstream1;

	for (int i = 0; i < num; i++) {
		sstream1 << iValue[i];
		if (i == (num - 1)) {
			break;
		}
		sstream1 << " ";
	}

	std::string str1 = sstream1.str();
	//::OutputDebugStringA(str1.c_str());
	int rtn = WritePrivateProfileStringA(iSection, iKey, str1.c_str(), iPath);

	return rtn;
}

#else

#include <iostream>
#include "hk_inifile.h"

//	INI file 形式のファイルから浮動小数データを読み取る
int kb::read(const char* iPath, const char* iSection, const char* iKey, double& oValue)
{
	std::string cstr1;
	bool rtn = hk::CIniFile::GetPrivateProfileString(iSection, iKey, cstr1,  iPath);
	if (rtn ) {
		oValue = atof(cstr1.c_str());
	}
	return (rtn)? 1 : 0;
}
int kb::read(const char* iPath, const char* iSection, const char* iKey, float& oValue)
{
	std::string cstr1;
	bool rtn = hk::CIniFile::GetPrivateProfileString(iSection, iKey, cstr1, iPath);
	if (rtn ) {
		oValue = atof(cstr1.c_str());
	}
	return (rtn) ? 1 : 0;
}

int kb::read(const char* iPath, const char* iSection, const char* iKey, std::string& oValue)
{
	std::string cstr1;
	bool rtn = hk::CIniFile::GetPrivateProfileString(iSection, iKey, cstr1, iPath);
	if (rtn ) {
		oValue = cstr1;
	}
	return (rtn) ? 1 : 0;
}

int kb::write(const char* iPath, const char* iSection, const char* iKey, std::string& iValue)
{
	bool rtn = hk::CIniFile::WritePrivateProfileString(iSection, iKey, iValue.c_str(), iPath);
	return (rtn) ? 1 : 0;
}

int kb::write(const char* iPath, const char* iSection, const char* iKey, const char* iValue)
{
	bool rtn = hk::CIniFile::WritePrivateProfileString(iSection, iKey, iValue, iPath);
	return (rtn) ? 1 : 0;
}


int kb::read(const char* iPath, const char* iSection, const char* iKey, int& oValue)
{
	std::string cstr1;
	bool rtn = hk::CIniFile::GetPrivateProfileString(iSection, iKey, cstr1, iPath);
	if (rtn ) {
		oValue = atoi(cstr1.c_str());
	}
	return (rtn) ? 1 : 0;
}

//	INI file 形式のファイルから浮動小数データを読み取る
int kb::read_csv(const char* iPath, const char* iSection, const char* iKey, double* oValue, int num)
{
	std::string cstr1;
	bool rtn = hk::CIniFile::GetPrivateProfileString(iSection, iKey, cstr1, iPath);



	if (rtn ) {
		std::istringstream stream(cstr1);

		//1行のうち、文字列とコンマを分割する
		for (int k = 0; k < num; k++) {
			std::string token;
			std::getline(stream, token, ',');
			size_t n1 = token.length();
			if (n1 == 0) {
			}
			else {
				oValue[k] = std::stod(token);
			}
			if (stream.eof() != false)
				break;
		}
	}
	return (rtn) ? 1 : 0;
}

//	INI file 形式のファイルから浮動小数データを読み取る
int kb::read_space(const char* iPath, const char* iSection, const char* iKey, double* oValue, int num)
{
	std::string cstr1;
	bool rtn = hk::CIniFile::GetPrivateProfileString(iSection, iKey, cstr1, iPath);

	if (rtn ) {
		std::stringstream sstream1(cstr1);
		std::string str2;
		for (int i = 0; i < num; i++) {
			sstream1 >> str2;
			oValue[i] = atof(str2.c_str());
		}
	}
	return (rtn) ? 1 : 0;
}


//	INI file 形式のファイルから浮動小数データを読み取る
int kb::write_csv(const char* iPath, const char* iSection, const char* iKey, double* iValue, int num)
{
	std::stringstream sstream1;

	for (int i = 0; i < num; i++) {
		sstream1 << iValue[i];
		if (i == (num - 1)) {
			break;
		}
		sstream1 << ",";
	}

	std::string str1 = sstream1.str();
	bool rtn = hk::CIniFile::WritePrivateProfileString(iSection, iKey, str1.c_str(), iPath);
	return (rtn) ? 1 : 0;
}

//	INI file 形式のファイルから浮動小数データを読み取る
int kb::write_space(const char* iPath, const char* iSection, const char* iKey, double* iValue, int num)
{
	std::stringstream sstream1;

	for (int i = 0; i < num; i++) {
		sstream1 << iValue[i];
		if (i == (num - 1)) {
			break;
		}
		sstream1 << " ";
	}

	std::string str1 = sstream1.str();
	bool rtn = hk::CIniFile::WritePrivateProfileString(iSection, iKey, str1.c_str(), iPath);
	return (rtn) ? 1 : 0;
}

//	INI file 形式のファイルから浮動小数データを読み取る
int kb::write(const char* iPath, const char* iSection, const char* iKey, double iValue)
{
	std::stringstream sstream1;

	sstream1 << iValue;

	std::string str1 = sstream1.str();
	//::OutputDebugStringA(str1.c_str());
	bool rtn = hk::CIniFile::WritePrivateProfileString(iSection, iKey, str1.c_str(), iPath);
	return (rtn) ? 1 : 0;
}

//	INI file 形式のファイルから浮動小数データを読み取る
int kb::write(const char* iPath, const char* iSection, const char* iKey, int iValue)
{
	std::stringstream sstream1;

	sstream1 << iValue;

	std::string str1 = sstream1.str();
	//::OutputDebugStringA(str1.c_str());
	bool rtn = hk::CIniFile::WritePrivateProfileString(iSection, iKey, str1.c_str(), iPath);
	return (rtn) ? 1 : 0;
}


//	INI file 形式のファイルから浮動小数データを読み取る
int kb::read_csv(const char* iPath, const char* iSection, const char* iKey, int* oValue, int num)
{
	std::string cstr1;
	bool rtn = hk::CIniFile::GetPrivateProfileString(iSection, iKey, cstr1, iPath);

	if (rtn ) {
		std::istringstream stream(cstr1);

		//1行のうち、文字列とコンマを分割する
		for (int k = 0; k < num; k++) {
			std::string token;
			std::getline(stream, token, ',');
			size_t n1 = token.length();
			if (n1 == 0) {
			}
			else {
				oValue[k] = std::stod(token);
			}
			if (stream.eof() != false)
				break;
		}
	}
	return (rtn) ? 1 : 0;
}

//	INI file 形式のファイルから浮動小数データを読み取る
int kb::read_space(const char* iPath, const char* iSection, const char* iKey, int* oValue, int num)
{
	std::string cstr1;
	bool rtn = hk::CIniFile::GetPrivateProfileString(iSection, iKey, cstr1, iPath);

	if (rtn ) {
		std::stringstream sstream1(cstr1);
		std::string str2;
		for (int i = 0; i < num; i++) {
			sstream1 >> str2;
			oValue[i] = atoi(str2.c_str());
		}
	}
	return (rtn) ? 1 : 0;
}


//	INI file 形式のファイルから浮動小数データを読み取る
int kb::write_csv(const char* iPath, const char* iSection, const char* iKey, int* iValue, int num)
{
	std::stringstream sstream1;

	for (int i = 0; i < num; i++) {
		sstream1 << iValue[i];
		if (i == (num - 1)) {
			break;
		}
		sstream1 << ",";
	}

	std::string str1 = sstream1.str();
	//::OutputDebugStringA(str1.c_str());
	bool rtn = hk::CIniFile::WritePrivateProfileString(iSection, iKey, str1.c_str(), iPath);
	return (rtn) ? 1 : 0;
}

int kb::write_space(const char* iPath, const char* iSection, const char* iKey, int* iValue, int num)
{
	std::stringstream sstream1;

	for (int i = 0; i < num; i++) {
		sstream1 << iValue[i];
		if (i == (num - 1)) {
			break;
		}
		sstream1 << " ";
	}

	std::string str1 = sstream1.str();
	//::OutputDebugStringA(str1.c_str());
	bool rtn = hk::CIniFile::WritePrivateProfileString(iSection, iKey, str1.c_str(), iPath);
	return (rtn) ? 1 : 0;
}


#endif