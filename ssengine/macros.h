#pragma once
#include <ssengine/core.h>

#if defined(__cplusplus)
extern "C"{
#endif

//TODO: save cache with dirty check.
//TODO: remove function ss_macro_eval

SS_CORE_API void ss_macro_define(ss_core_context* C, const char* name, const char* val);
SS_CORE_API void ss_macro_undefine(ss_core_context* C, const char* name);
SS_CORE_API int ss_macro_isdef(ss_core_context* C, const char* name);

SS_CORE_API void ss_macro_eval(ss_core_context* C, const char* name);
SS_CORE_API size_t ss_macro_get_length(ss_core_context* C, const char* name);
SS_CORE_API int ss_macro_get_content(ss_core_context* C, const char* name, char* buf, size_t sz);

SS_CORE_API int ss_macro_get_integer(ss_core_context* C, const char* name);

#if defined(__cplusplus)
}
#endif


#if defined(__cplusplus)
#include <string>
SS_CORE_API const std::string& ss_macro_get_content(ss_core_context* C, const char* name);
#endif