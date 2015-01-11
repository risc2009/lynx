cmake_minimum_required(VERSION 3.0)

project(lynx)

add_executable(lynx WIN32 MACOSX_BUNDLE main.cpp)

if(APPLE)
	set_target_properties(lynx PROPERTIES COMPILE_FLAGS -ObjC++)
	find_library(COCOA_LIBRARY Cocoa)
	mark_as_advanced (COCOA_LIBRARY)
	set(EXTRA_LIBS ${COCOA_LIBRARY})
	target_link_libraries(lynx ${EXTRA_LIBS})
endif(APPLE)
