#include <string>


#pragma once

namespace kb
{
	//	現在のアプリケーションのファイルパスを取得する
	void get_module_directory(HINSTANCE hInstance, std::string& dname1);

	//	実行ファイルを呼び出す
	int run_exe(std::string& iPath, BOOL iConsole, DWORD* o_dwExitCode, DWORD* o_dwError, LPCTSTR iCurrentPath, int test1);

};

