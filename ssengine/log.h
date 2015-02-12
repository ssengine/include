#pragma once
#include <ssengine/ssengine.h>

#if defined(_MSC_VER) && _MSC_VER>=1700
#   include <stdio.h>
#   define _SS_LOG_FORMAT_ARGUMENT_  _Printf_format_string_
#else
#   define _SS_LOG_FORMAT_ARGUMENT_
#endif


#define SS_LL_TRACE		(0)
#define SS_LL_INFO		(1)
#define SS_LL_WARN		(2)
#define SS_LL_ERROR		(3)
#define SS_LL_FATAL		(4)

SS_CORE_API void ss_log(int level, _SS_LOG_FORMAT_ARGUMENT_ const char* format, ...);
SS_CORE_API void ss_wlog(int level, _SS_LOG_FORMAT_ARGUMENT_ const wchar_t* format, ...);

typedef struct ss_logger
{
	void* userdata;
	void(*log)(int level, const char* msg, size_t sz, void* userdata);
	void(*wlog)(int level, const wchar_t* msg, size_t sz, void* userdata);
} ss_logger;

void SS_CORE_API ss_add_logger(ss_logger* logger);
void SS_CORE_API ss_remove_logger(ss_logger* logger);

#define SS_LOG ss_log
#define SS_WLOG ss_wlog

#define SS_LOGT(fmt, ...) ss_log(SS_LL_TRACE, fmt, __VA_ARGS__)
#define SS_LOGI(fmt, ...) ss_log(SS_LL_INFO, fmt, __VA_ARGS__)
#define SS_LOGW(fmt, ...) ss_log(SS_LL_WARN, fmt, __VA_ARGS__)
#define SS_LOGE(fmt, ...) ss_log(SS_LL_ERROR, fmt, __VA_ARGS__)
#define SS_LOGF(fmt, ...) ss_log(SS_LL_FATAL, fmt, __VA_ARGS__)

#define SS_WLOGT(fmt, ...) ss_wlog(SS_LL_TRACE, fmt, __VA_ARGS__)
#define SS_WLOGI(fmt, ...) ss_wlog(SS_LL_INFO, fmt, __VA_ARGS__)
#define SS_WLOGW(fmt, ...) ss_wlog(SS_LL_WARN, fmt, __VA_ARGS__)
#define SS_WLOGE(fmt, ...) ss_wlog(SS_LL_ERROR, fmt, __VA_ARGS__)
#define SS_WLOGF(fmt, ...) ss_wlog(SS_LL_FATAL, fmt, __VA_ARGS__)

#ifdef NDEBUG
#define SS_DEBUG(lvl, fmt, ...)
#define SS_WDEBUG(lvl, fmt, ...)
#else
#define SS_DEBUG ss_log
#define SS_WDEBUG ss_logw
#endif

#define SS_DEBUGT(fmt, ...) SS_DEBUG(SS_LL_TRACE, fmt, __VA_ARGS__)
#define SS_DEBUGI(fmt, ...) SS_DEBUG(SS_LL_INFO, fmt, __VA_ARGS__)
#define SS_DEBUGW(fmt, ...) SS_DEBUG(SS_LL_WARN, fmt, __VA_ARGS__)
#define SS_DEBUGE(fmt, ...) SS_DEBUG(SS_LL_ERROR, fmt, __VA_ARGS__)
#define SS_DEBUGF(fmt, ...) SS_DEBUG(SS_LL_FATAL, fmt, __VA_ARGS__)

#define SS_WDEBUGT(fmt, ...) SS_WDEBUG(SS_LL_TRACE, fmt, __VA_ARGS__)
#define SS_WDEBUGI(fmt, ...) SS_WDEBUG(SS_LL_INFO, fmt, __VA_ARGS__)
#define SS_WDEBUGW(fmt, ...) SS_WDEBUG(SS_LL_WARN, fmt, __VA_ARGS__)
#define SS_WDEBUGE(fmt, ...) SS_WDEBUG(SS_LL_ERROR, fmt, __VA_ARGS__)
#define SS_WDEBUGF(fmt, ...) SS_WDEBUG(SS_LL_FATAL, fmt, __VA_ARGS__)

