#pragma once

#include <ssengine/resource.h>
#include <ssengine/render/device.h>

typedef ss_resource_reference<ss_texture> ss_texture_resource_ref;
typedef ss_resource_reference<ss_texture2d> ss_texture2d_resource_ref;

SS_CORE_API ss_texture2d_resource_ref* ss_texture2d_resource(ss_core_context* C, const char* uri);