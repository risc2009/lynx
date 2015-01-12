# PLATFORM
# OSを定義
# APPLE社のOSの場合に定義
# MacOSX          MacOS X
# iPhoneOS        iOS（実機）
# iPhoneSimulator iOS（シミュレータ）

# PLATFORM_VERSION
# バージョンを定義

cmake_minimum_required(VERSION 3.0)

project(lynx)

if(APPLE)
	if(NOT DEFINED PLATFORM)
		set(PLATFORM "MacOSX")
	endif(NOT DEFINED PLATFORM)
	message(STATUS "PLATFORM=${PLATFORM}")

	set(XCODE_DEVELOPER_ROOT "/Applications/Xcode.app/Contents/Developer/Platforms/${PLATFORM}.platform/Developer")
	if(NOT EXISTS ${XCODE_DEVELOPER_ROOT})
		message(FATAL_ERROR "No SDK ROOT Folder Found.")
	endif(NOT EXISTS ${XCODE_DEVELOPER_ROOT})
	set(CMAKE_C_COMPILER "${XCODE_DEVELOPER_ROOT}/Toolchains/XcodeDefault.xctoolchain/usr/bin/clang")
	set(CMAKE_CXX_COMPILER "${XCODE_DEVELOPER_ROOT}/Toolchains/XcodeDefault.xctoolchain/usr/bin/clang++")
	set(CMAKE_AR "${XCODE_DEVELOPER_ROOT}/Toolchains/XcodeDefault.xctoolchain/usr/bin/ar")
	set(CMAKE_RANLIB "${XCODE_DEVELOPER_ROOT}/Toolchains/XcodeDefault.xctoolchain/usr/bin/ranlib")

	if(NOT DEFINED PLATFORM_VERSION)
		file (GLOB _CMAKE_SDKS "${XCODE_DEVELOPER_ROOT}/SDKs/*")
		if(_CMAKE_SDKS)
			list(SORT _CMAKE_SDKS)
			list(REVERSE _CMAKE_SDKS)
			list (GET _CMAKE_SDKS 0 CMAKE_SDK_ROOT)
		else(N_CMAKE_SDKS)
			message(FATAL_ERROR "No Sdk Root Found. _CMAKE_SDKS=${_CMAKE_SDKS}")
		endif(_CMAKE_SDKS)
	else(NOT DEFINED PLATFORM_VERSION)
		set(CMAKE_SDK_ROOT ${XCODE_DEVELOPER_ROOT}/SDKs/${PLATFORM}${PLATFORM_VERSION}.sdk)
		if(NOT EXISTS ${CMAKE_SDK_ROOT})
			message(FATAL_ERROR "No Sdk Root Found. CMAKE_SDK_ROOT=${CMAKE_SDK_ROOT}")
		endif(NOT EXISTS ${CMAKE_SDK_ROOT})
	endif(NOT DEFINED PLATFORM_VERSION)
	set(CMAKE_SYSTEM_FRAMEWORK_PATH
		${CMAKE_SDK_ROOT}/System/Library/Frameworks
		${CMAKE_SDK_ROOT}/System/Library/PrivateFrameworks
		${CMAKE_SDK_ROOT}/Developer/Library/Frameworks)
	message (STATUS "CMAKE_SDK_ROOT=${CMAKE_SDK_ROOT}")

	if(${PLATFORM} STREQUAL "iPhoneOS")
		set(CPU_ARCH armv7)
	endif(${PLATFORM} STREQUAL "iPhoneOS")
endif(APPLE)

add_executable(lynx WIN32 MACOSX_BUNDLE main.cpp)

if(APPLE)
	if(DEFINED CPU_ARCH)
		set_target_properties(lynx PROPERTIES COMPILE_FLAGS "-ObjC++ -arch ${CPU_ARCH} -isysroot ${CMAKE_SDK_ROOT}")
	else(DEFINED CPU_ARCH)
		set_target_properties(lynx PROPERTIES COMPILE_FLAGS "-ObjC++ -isysroot ${CMAKE_SDK_ROOT}")
	endif(DEFINED CPU_ARCH)
	if(${PLATFORM} STREQUAL "MacOSX")
		find_library(COCOA_LIBRARY Cocoa)
		mark_as_advanced (COCOA_LIBRARY)
		set(EXTRA_LIBS ${COCOA_LIBRARY})
	else(${PLATFORM} STREQUAL "MacOSX")
		find_library(UIKIT_LIBRARY UIKit)
		mark_as_advanced (UIKIT_LIBRARY)
		set(EXTRA_LIBS ${UIKIT_LIBRARY})
	endif(${PLATFORM} STREQUAL "MacOSX")
	target_link_libraries(lynx ${EXTRA_LIBS})
endif(APPLE)
