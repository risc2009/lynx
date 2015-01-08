//
//  main
//  lynx
//
//  Created by nomura 15/1/8
//  Copyright(c) 2015 nomura. All rights reversed.

#ifdef _WIN32
#include<windows.h>
#else
#endif

#ifdef _WIN32
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev,PSTR lpCmdLine, int nCmdShow) {
	int C_ARGC;
	LPWSTR *C_ARGV = CommandLineToArgvW(GetCommandLineW(), &C_ARGC);
	if ( NULL == C_ARGV) return -1;
#else
int main(int C_ARGC,const char *C_ARGV[]) {
#endif

#ifdef _WIN32
	LocalFree(C_ARGV);
#endif
	return 0;
}
