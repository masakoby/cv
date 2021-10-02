
#include <string>
#pragma once

namespace kb
{

	//	INI file 形式のファイルからデータを読み取る
	//	読みとれなかった場合、戻り値が０となる。
	//	読みとれたとき、戻り値に読みとった文字数が返る
	int read(const char* iPath, const char* iSection, const char* iKey, std::string& oValue);
	int write(const char* iPath, const char* iSection, const char* iKey, std::string& iValue);
	int write(const char* iPath, const char* iSection, const char* iKey, const char* iValue);

	//	INI file 形式のファイルから整数データを読み取る
	int read(const char* iPath, const char* iSection, const char* iKey, int& oValue);
	//	INI file 形式のファイルから整数データを読み取る
	int read(const char* iPath, const char* iSection, const char* iKey, short& oValue);
	//	INI file 形式のファイルから浮動小数データを読み取る
	int read(const char* iPath, const char* iSection, const char* iKey, double& oValue);
	int read(const char* iPath, const char* iSection, const char* iKey, float& oValue);

	//	INI file 形式のファイルから浮動小数データを読み取る
	int read_csv(const char* iPath, const char* iSection, const char* iKey, double* oValue, int num);
	int read_space(const char* iPath, const char* iSection, const char* iKey, double* oValue, int num);
	//	INI file 形式のファイルから浮動小数データを読み取る
	int write_csv(const char* iPath, const char* iSection, const char* iKey, double* oValue, int num);
	int write_space(const char* iPath, const char* iSection, const char* iKey, double* oValue, int num);

	int write(const char* iPath, const char* iSection, const char* iKey, double oValue);
	int write(const char* iPath, const char* iSection, const char* iKey, int oValue);

	//	INI file 形式のファイルから浮動小数データを読み取る
	int read_csv(const char* iPath, const char* iSection, const char* iKey, int* oValue, int num);
	int read_space(const char* iPath, const char* iSection, const char* iKey, int* oValue, int num);
	//	INI file 形式のファイルから浮動小数データを読み取る
	int write_csv(const char* iPath, const char* iSection, const char* iKey, int* oValue, int num);
	int write_space(const char* iPath, const char* iSection, const char* iKey, int* oValue, int num);

};