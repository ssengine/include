#pragma once

#include <ssengine/ssengine.h>

typedef struct ss_core_context ss_core_context;

#ifdef __cplusplus
extern "C" {
#endif

SS_CORE_API ss_core_context* ss_create_context();

SS_CORE_API void ss_destroy_context(ss_core_context* C);


//TODO: move to another place.
#include <lua.h>

SS_CORE_API lua_State* ss_get_script_context(ss_core_context* C);

SS_CORE_API ss_core_context* ss_lua_get_core_context(lua_State* L);

SS_CORE_API void ss_lua_preload_module(lua_State* L, const char* name, lua_CFunction func);

#if defined(__cplusplus)
SS_CORE_API void ss_run_script_from_macro(ss_core_context* C, const char* name, int nargs = 0, int nrets = 0);
#else
SS_CORE_API void ss_run_script_from_macro(ss_core_context* C, const char* name, int nargs, int nrets);
#endif

SS_CORE_API int luaL_loaduri(lua_State* L, const char* uri);

SS_CORE_API int luaL_loadurix(lua_State* L, const char* uri, const char* mode);

// Invoke a function. 
// If any error occurred, post error msg to log and returns nothing.
SS_CORE_API void ss_safe_call(lua_State* L, int nargs, int nrets);

#ifdef __cplusplus
}
#endif