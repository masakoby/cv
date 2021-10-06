//#include "stdafx.h"

#include <Windows.h>
#include "kb_run_exe.h"
#include <io.h>
//#include <fstream>

//#pragma comment( lib, "shell32.lib" )



//	現在のアプリケーションのファイルパスを取得する
void kb::get_module_directory(HINSTANCE hInstance, std::string& dname1)
{
	char path1[4096] ;
	if( ::GetModuleFileNameA(hInstance, path1, 4096)==0 )
		return ;
	std::string path2=path1;

	int n1=path2.find_last_of("\\");
	int n2=path2.find_last_of("/");
		
	if( n1<n2 ){ n1=n2;	}

	std::string path3=path2.substr(0, n1);

//		printf(path3.c_str());
	dname1=path3;
}


int kb::run_exe(std::string& iPath, BOOL iConsole, DWORD* o_dwExitCode, DWORD* o_dwError, LPCTSTR iCurrentPath, int test1)
{
	std::string strD1=iPath;	//TRACE(strD1);

	PROCESS_INFORMATION pi;
	STARTUPINFO si;
	ZeroMemory(&si,sizeof(si));
	ZeroMemory(&pi,sizeof(pi));
	si.cb=sizeof(si);

	DWORD cflg=CREATE_NEW_CONSOLE;
	if( iConsole==FALSE ){
		cflg=CREATE_NO_WINDOW;
	}

	LPSTR p1=(LPSTR)strD1.c_str();
	BOOL rtnP=::CreateProcess(
		p1,
		NULL,
		NULL,NULL,
		FALSE,
		cflg,
		NULL,iCurrentPath,
		&si,&pi
		);

	if( rtnP==FALSE ){
		DWORD dwError=GetLastError();
		DWORD dwExitCode=0;
		GetExitCodeProcess(pi.hProcess, &dwExitCode);

		*o_dwExitCode	=dwExitCode;
		*o_dwError		=dwError;

		return -1;
	}

	if( test1>0 ){
		//	プライマリスレッドのハンドルを放す
		CloseHandle(pi.hThread);
		//	プロセスが終了するのを待つ
		WaitForSingleObject(pi.hProcess,INFINITE);

		//	プロセス終了時のエラーを取得
		DWORD dwError=GetLastError();

		//	プロセス終了コードを取得
		DWORD dwExitCode=0;
		GetExitCodeProcess(pi.hProcess, &dwExitCode);

		//	プロセスのハンドルを放す
		CloseHandle(pi.hProcess);

		*o_dwExitCode	=dwExitCode;
		*o_dwError		=dwError;
	}

	return 0;
}


