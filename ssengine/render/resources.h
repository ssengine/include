#pragma once

#include <ssengine/resource.h>
#include <ssengine/render/device.h>

typedef ss_resource_reference<ss_texture> ss_texture_resource_ref;

ss_texture_resource_ref* ss_texture_resource(ss_core_context* C, const char* uri);