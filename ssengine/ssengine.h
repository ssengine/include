#pragma once


#if defined(WIN32)
	#if defined(SS_CORE)
		#define SS_CORE_API __declspec(dllexport)
	#else
		#define SS_CORE_API __declspec(dllimport)
	#endif
#else
	#define SS_CORE_API
#endif

#include <wchar.h>

//TODO: move to another place.
SS_CORE_API wchar_t* char2wchar_t(const char*);
SS_CORE_API char* wchar_t2char(const wchar_t*);