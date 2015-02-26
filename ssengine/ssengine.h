#pragma once
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#if defined(WIN32)
	#if defined(BUILDING_SS_CORE)
		#define SS_CORE_API __declspec(dllexport)
	#else
		#define SS_CORE_API __declspec(dllimport)
	#endif
#else
	#define SS_CORE_API
#endif

#if defined(WIN32)
	#define SS_EXPORT __declspec(dllexport)
#else
	#define SS_EXPORT 
#endif

#include <wchar.h>

#if defined(__cplusplus)
extern "C"{
#endif

//TODO: move to another place.
SS_CORE_API wchar_t* char2wchar_t(const char*);
SS_CORE_API char* wchar_t2char(const wchar_t*);

#ifdef __cplusplus
}
#include <string>

inline std::wstring string2wstring(const std::string& str){
	wchar_t* tmp = char2wchar_t(str.c_str());
	std::wstring ret = tmp;
	delete[] tmp;
	return ret;
}
inline std::string wstring2string(const std::wstring& other){
	char* tmp = wchar_t2char(other.c_str());
	std::string ret = tmp;
	delete[] tmp;
	return ret;
}

#endif

