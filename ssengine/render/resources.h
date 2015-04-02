#pragma once

#include <ssengine/resource.h>
#include <ssengine/render/device.h>

#ifdef __cplusplus
extern "C" {
#endif

SS_CORE_API ss_resource_ref* ss_texture2d_resource(ss_core_context* C, const char* uri);

const ss_resource_type*  ss_texture2d_resource_typetag();

#ifdef __cplusplus
}
typedef ss_resource_reference<ss_texture> ss_texture_resource_ref;
typedef ss_resource_reference<ss_texture2d> ss_texture2d_resource_ref;

inline ss_resource_reference<ss_texture2d>* ss_resource_reference<ss_texture2d>::get(ss_core_context* C, const char* uri){
    return wrap(ss_texture2d_resource(C, uri));
}

inline const ss_resource_type* ss_resource_reference<ss_texture2d>::typetag(){
    return ss_texture2d_resource_typetag();
}
#endif
