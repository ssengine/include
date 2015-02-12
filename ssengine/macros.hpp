#pragma once
extern "C"{
#include <ssengine/macros.h>
}

#include <string>
SS_CORE_API const std::string & ss_macro_get_content(const char* name);