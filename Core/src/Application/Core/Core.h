#pragma once

#ifdef PROJECT_BUILD_DLL 
	#define  __declspec(dllexport)
#else
	#define  __declspec(dllimport)
#endif
