#pragma once
#include <ssengine/ssengine.h>

//TODO: save cache with dirty check.
//TODO: remove function ss_macro_eval

void SS_CORE_API ss_macro_define(const char* name, const char* val);
void SS_CORE_API ss_macro_undefine(const char* name);
int SS_CORE_API ss_macro_isdef(const char* name);

void SS_CORE_API ss_macro_eval(const char* name);
size_t SS_CORE_API ss_macro_get_length(const char* name);
int SS_CORE_API ss_macro_get_content(const char* name, char* buf, size_t sz);

int SS_CORE_API ss_macro_get_integer(const char* name);