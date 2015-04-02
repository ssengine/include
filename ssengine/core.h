#pragma once

#include <ssengine/ssengine.h>

typedef struct ss_core_context ss_core_context;

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

SS_CORE_API ss_core_context* ss_create_context();

SS_CORE_API void ss_destroy_context(ss_core_context* C);

// render device

typedef struct ss_render_device ss_render_device;

SS_CORE_API ss_render_device*  ss_get_render_device(ss_core_context* C);

SS_CORE_API void ss_set_render_device(ss_core_context* C, ss_render_device* device);

// script context

typedef struct lua_State lua_State;
typedef int(*lua_CFunction) (lua_State *L);

SS_CORE_API lua_State* ss_get_script_context(ss_core_context* C);

SS_CORE_API ss_core_context* ss_lua_get_core_context(lua_State* L);

SS_CORE_API void ss_lua_preload_module(lua_State* L, const char* name, lua_CFunction func);

#if defined(__cplusplus)
SS_CORE_API void ss_run_script_from_macro(ss_core_context* C, const char* name, int nargs = 0, int nrets = 0);
#else
SS_CORE_API void ss_run_script_from_macro(ss_core_context* C, const char* name, int nargs, int nrets);
#endif

SS_CORE_API void ss_cache_script_from_macro(lua_State* L, const char* name, void* tagPointer);

SS_CORE_API int luaL_loaduri(lua_State* L, const char* uri);

SS_CORE_API int luaL_loadurix(lua_State* L, const char* uri, const char* mode);

// Invoke a function. 
// If any error occurred, post error msg to log and returns nothing.
SS_CORE_API void ss_lua_safe_call(lua_State* L, int nargs, int nrets);

SS_CORE_API void ss_lua_push_resource_ref(lua_State* L, struct ss_resource_ref* res);

#ifdef __cplusplus
#include <lauxlib.h>
inline struct ss_resource_ref*& ss_lua_check_resource_ref(lua_State* L, int pos){
    return *reinterpret_cast<struct ss_resource_ref**>(luaL_checkudata(L, pos, "Resource"));
}

#else
#define ss_lua_check_resource_ref(L, pos) *((struct ss_resource_ref**)luaL_checkudata(L, pos, "Resource"))
#endif

#ifdef __cplusplus
}

template <typename res_type>
struct ss_resource_reference;

template <typename T>
inline ss_resource_reference<T>*& ss_lua_check_resource_reference(lua_State* L, int pos){
    ss_resource_reference<T>*& ret = *reinterpret_cast<struct ss_resource_reference<T>**>(luaL_checkudata(L, pos, "Resource"));
    if (ret->prototype->typetag != ss_resource_reference<T>::typetag()){
        //TODO: display error message with actual resource type.
        luaL_typerror(L, pos, "Resource");
    }
    return ret;
}
#endif
