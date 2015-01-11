//
//  main.cpp
//  lynx
//
//  Created by nomura 15/1/8
//  Copyright(c) 2015 nomura. All rights reversed.

/* **** */
/* MEMO */
/* **** */
// _WIN32                 ：Windows(32bit/64bit)の場合に定義される
// _WIN64                 ：Windows(64bit)の場合に定義される
// __APPLE__              ：MacOS X / iOS(実機 / シミュレータ）の場合に定義される
// TARGET_OS_IPHONE       ：iOS(実機 / シミュレータ）の場合に定義される
// TARGET_IPHONE_SIMULATOR：iOS（シミュレータ）の場合に定義される

#ifdef _WIN32
#  include<windows.h>
#elif __APPLE__
#  ifdef TARGET_OS_IPHONE
#    import <UIKit/UIKit.h>
#  else
#    import <Cocoa/Cocoa.h>
#  endif
#endif

#ifdef _WIN32
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, PSTR lpCmdLine,
                   int nCmdShow) {
	int C_ARGC;
	LPWSTR *C_ARGV = CommandLineToArgvW(GetCommandLineW(), &C_ARGC);
	if (NULL == C_ARGV) {
		return -1;
	}
#else
int main(int C_ARGC, const char *C_ARGV[]) {
#endif

    int ret;
#ifdef _WIN32
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    ret = 0;
#elif __APPLE__
#  if TARGET_OS_IPHONE
    @autoreleasepool {
        ret = UIApplicationMain(C_ARGC, C_ARGV, nil,
                                NSStringFromClass([AppDelegate class]));
    }
#  else 
    ret = NSApplicationMain(C_ARGC, C_ARGV);
#  endif
#endif

#ifdef _WIN32
	LocalFree(C_ARGV);
#endif
	return ret;
}
