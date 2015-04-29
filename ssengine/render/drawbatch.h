#pragma once

#include <ssengine/ssengine.h>
#include <ssengine/render/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ss_core_context ss_core_context;
typedef struct ss_texture2d ss_texture2d;

//SS_CORE_API void ss_db_discard(ss_core_context* C);

SS_CORE_API void ss_db_flush(ss_core_context* C);

SS_CORE_API void ss_db_draw_line(
    ss_core_context* C, 
    const ss_matrix& matrix,
    float x0, float y0, float x1, float y1);


SS_CORE_API void ss_db_draw_image_rect(
    ss_core_context* C,
    const ss_matrix& matrix,
    ss_texture2d*	 texture,
    float l, float t, float w, float h,
    float tl, float tt, float tw, float th
    );

#ifdef __cplusplus
}

#endif

#ifdef __cplusplus
#include <ssengine/render/types.h>

inline void ss_db_draw_line(ss_core_context* C, const ss_matrix& matrix, ss::float2 from, ss::float2 to){
	ss_db_draw_line(C, matrix, from.x, from.y, to.x, to.y);
}

struct render2d_context
{
    ss_core_context *C;
    ss::matrix_stack matrix_stack;
};

#include <lua.hpp>
inline struct render2d_context* ss_lua_check_render2d_context(lua_State* L, int pos){
    return reinterpret_cast<struct render2d_context*>(luaL_checkudata(L, pos, "render2d.Context"));
}

#include <ssengine/render/device.h>
#include <ssengine/render/types.h>

typedef struct ss_draw_batch{
    virtual void flush() = 0;

    virtual void prepare(ss_primitive_type pt, size_t count) = 0;
    virtual void prepare(ss_texture2d* texture, ss_primitive_type pt, size_t count) = 0;
    virtual void prepare(ss_render_technique* tech, ss_primitive_type pt, size_t count) = 0;
    virtual void prepare(ss_render_technique* tech, ss_texture2d* texture, ss_primitive_type pt, size_t count) = 0;

    virtual ss::float2& pos(size_t idx) = 0;
    virtual ss::color& diffuse(size_t idx) = 0;
    virtual ss::float2& texcoord(size_t idx) = 0;
protected:
    ~ss_draw_batch(){}
} ss_draw_batch;

extern "C" SS_CORE_API ss_draw_batch* ss_core_get_draw_batch(ss_core_context* C);
#endif