#pragma once

#include <ssengine/ssengine.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ss_core_context ss_core_context;

//SS_CORE_API void ss_db_discard(ss_core_context* C);

SS_CORE_API void ss_db_flush(ss_core_context* C);

SS_CORE_API void ss_db_draw_line(ss_core_context* C, float x0, float y0, float x1, float y1);




#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
#include <ssengine/render/types.h>

inline void ss_db_draw_line(ss_core_context* C, ss::float2 from, ss::float2 to){
	ss_db_draw_line(C, from.x, from.y, to.x, to.y);
}

#endif