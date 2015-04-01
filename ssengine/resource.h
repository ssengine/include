#pragma once

#include <ssengine/core.h>

#include <stdbool.h>

#ifdef __cplusplus
extern "C"{
#endif

enum ss_device_types{
	SS_DT_SOFTWARE	= 0,
	SS_DT_RENDER	= 1,
	SS_DT_AUDIO		= 2,

	SS_DT_USER		= 0x100
};

typedef struct ss_resource_prototype ss_resource_prototype;

typedef struct ss_resource_ref{
	const ss_resource_prototype* const	prototype;
	const int							device_type;
	void*								ptr;
} ss_resource_ref;

typedef struct ss_resource_type{}  ss_resource_type;

typedef struct ss_resource_prototype{
	const ss_resource_type*const typetag;

	int(*sync_load)(ss_core_context* C, ss_resource_ref* res);

	void(*async_load)(ss_core_context* C, ss_resource_ref* res);

	void(*unload)(ss_core_context* C, ss_resource_ref* res);
} ss_resource_prototype;

// All these functions should be invoke in main thread.
// But the resource loading process maybe run in another.

SS_CORE_API ss_resource_ref* ss_resource_from_uri(ss_core_context* C, const char* uri);

SS_CORE_API void ss_resource_release(ss_core_context* C, ss_resource_ref* ref);

SS_CORE_API void ss_resource_addref(ss_core_context* C, ss_resource_ref* ref);

SS_CORE_API ss_resource_ref* ss_resource_create(ss_core_context* C, const ss_resource_prototype* prototype, const char* uri, int device_type);



SS_CORE_API int ss_get_user_device_type(ss_core_context* C, const char* name);

SS_CORE_API void ss_open_device(ss_core_context* C, int device_type);

SS_CORE_API void ss_close_device(ss_core_context* C, int device_type);

SS_CORE_API bool ss_is_device_open(ss_core_context* C, int device_type);



SS_CORE_API int ss_resource_load(ss_core_context* C, ss_resource_ref* ref);

SS_CORE_API void ss_resource_async_load(ss_core_context* C, ss_resource_ref* ref);

SS_CORE_API void ss_resource_unload(ss_core_context* C, ss_resource_ref* ref);

SS_CORE_API void ss_resource_async_unload(ss_core_context* C, ss_resource_ref* ref);

SS_CORE_API bool ss_resource_is_loading(ss_core_context* C, ss_resource_ref* ref);

#ifdef __cplusplus
}

//TODO: Reimplement me as a smart pointer.
template <typename res_type>
struct ss_resource_reference
{
	typedef res_type res_type;
	typedef ss_resource_reference<res_type> this_type;

	struct ss_resource_prototype* const	prototype;
	const int							device_type;

	res_type* get(){
		return ptr;
	}

	static this_type* wrap(ss_resource_ref* ref){
		return reinterpret_cast<this_type*>(ref);
	}

	static const this_type* wrap(const ss_resource_ref* ref){
		return reinterpret_cast<const this_type*>(ref);
	}

    ss_resource_ref* unwrap(){
        return reinterpret_cast<ss_resource_ref*>(this);
    }

    const ss_resource_ref* unwrap() const{
        return reinterpret_cast<const ss_resource_ref*>(this);
    }

    static this_type* get(ss_core_context* C, const char* uri);
private:
	res_type*						ptr;
};

#endif
