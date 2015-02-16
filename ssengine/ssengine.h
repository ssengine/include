#pragma once


#if defined(WIN32)
	#if defined(BUILDING_SS_CORE)
		#define SS_CORE_API __declspec(dllexport)
	#else
		#define SS_CORE_API __declspec(dllimport)
	#endif
#else
	#define SS_CORE_API
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

extern "C"{
#endif


//TODO: move to another place.
#include <lua.h>

SS_CORE_API lua_State* ss_init_script_context();

SS_CORE_API void ss_destroy_script_context();

SS_CORE_API lua_State* ss_get_script_context();

SS_CORE_API void ss_preload_module(const char* name, lua_CFunction func);

#if defined(__cplusplus)
SS_CORE_API void ss_run_script_from_macro(const char* name, int nargs = 0, int nrets = 0);
#else
SS_CORE_API void ss_run_script_from_macro(const char* name, int nargs, int nrets);
#endif

// Invoke a function. 
// If any error occurred, post error msg to log and returns nothing.
SS_CORE_API void ss_safe_call(lua_State* L, int nargs, int nrets);

#if defined(__cplusplus)
}
#endif