#pragma once

#include <ssengine/ssengine.h>

struct ss_color{
	float r, g, b, a;
};

enum ss_render_device_type{
	SS_RDT_ANY		= 0xffffffff,

	SS_RDT_NULL		= 0x0,
	SS_RDT_SOFTWARE  = 0x1,

	SS_RDT_OPENGL = 0x10,
	SS_RDT_OPENGLES = 0x11,

	SS_RDT_DIRECTX9 = 0x20,
	SS_RDT_DIRECTX10 = 0x21,
	SS_RDT_DIRECTX11 = 0x22,
	SS_RDT_DIRECTX12 = 0x23
};

enum ss_clear_flags{
	SS_CF_NONE		= 0x0,
	SS_CF_COLOR		= 0x1,
	SS_CF_DEPTH		= 0x2,
	SS_CF_STENCIL	= 0x4
};

enum ss_primitive_type{
	SS_PT_NULL			= 0x0,
	SS_PT_POINTLIST		= 0x1,
	SS_PT_LINELIST		= 0x2,
	SS_PT_LINESTRIP		= 0x3,
	SS_PT_TRIANGLELIST	= 0x4,
	SS_PT_TRIANGLESTRIP	= 0x5,
};

enum ss_render_format{
	SS_FORMAT_NULL			= 0x0,
	SS_FORMAT_FLOAT32_RGBA	= 0x1,
	SS_FORMAT_BYTE_RGBA		= 0x2,
	SS_FORMAT_FLOAT32_RG    = 0x3,
	SS_FORMAT_BYTE_BGRA     = 0x4,
};

inline size_t ss_render_format_sizeof(ss_render_format type){
	static size_t sizes[] = {
		0, 16, 4, 8
	};
	int iType = (int)type;
	if (iType >= 0 && iType <= 2){
		return sizes[iType];
	}
	return 0;
}

struct ss_buffer{
	virtual ~ss_buffer() = 0{}
};

struct ss_buffer_memory : ss_buffer{
	virtual void* lock() = 0;
	virtual void unlock() = 0;
	virtual void copy(size_t ofs, void* src, size_t sz) = 0;
};

struct ss_buffer_static : ss_buffer{

};

struct ss_buffer_managed : ss_buffer{

};

enum ss_render_input_usage_type{
	SS_USAGE_NONE		= 0,
	SS_USAGE_POSITION	= 1,
	SS_USAGE_DIFFUSE	= 2,
	SS_USAGE_TEXCOORD	= 3,
	SS_USAGE_NORMAL		= 4
};

struct ss_render_input_usage{
	ss_render_input_usage_type	type;
	unsigned int				index;

	ss_render_input_usage(
		ss_render_input_usage_type _type = SS_USAGE_NONE,
		unsigned _index = 0)
		: type(_type), index(_index)
	{
	}

	bool operator == (const ss_render_input_usage& other) const{
		return type == other.type && index == other.index;
	}
};

struct ss_render_input_element
{
	ss_render_input_usage	usage;
	unsigned int			index;		//index of array or matrix
	ss_render_format		format;
	unsigned int			slot;		//slot of vertex buffer
	unsigned int			alignOffset;
};

struct ss_render_input_layout{
	virtual ~ss_render_input_layout() = 0 {}
};

struct ss_render_pass{
protected:
	~ss_render_pass(){}
public:
	virtual void begin() = 0;
	virtual void end() = 0;
};

struct ss_render_technique{
	virtual ~ss_render_technique() = 0 {};
	virtual size_t pass_count() = 0;
	virtual ss_render_pass* get_pass(size_t index) = 0;

	virtual ss_render_input_layout* create_input_layout(
		ss_render_input_element* elements,
		size_t		count
		) = 0;

};

enum ss_predefined_technique_type{
	SS_PDT_BLANK				= 0,
	SS_PDT_STANDARD_NO_TEXTURE	= 1,
	SS_PDT_STANDARD				= 2,
	SS_PDT_GREY					= 3
};

struct ss_texture{
	virtual ~ss_texture() = 0 {};
};

struct ss_texture2d : ss_texture{
};

struct ss_render_device
{
	//TODO: CheckFeatureSupport
	//TODO: CheckFormatSupport

	virtual ~ss_render_device(){}
	
	virtual void clear_color(const ss_color& color) = 0;

	void clear_color(float r, float g, float b, float a){
		ss_color c = { r, g, b, a };
		clear_color(c);
	}
	
	virtual void clear(int flags = SS_CF_COLOR) = 0;
	virtual void present() = 0;

	virtual void set_viewport(int left, int top, int width, int height) = 0;

	void destroy(){ delete this; };

	virtual void set_primitive_type(ss_primitive_type mt) = 0;

	virtual void draw(int count, int from) = 0;
	virtual void draw_index(int count, int from, int base) = 0;

	virtual ss_buffer_memory* create_memory_buffer(
		size_t bytes) = 0;

	virtual ss_render_technique* get_predefined_technique(ss_predefined_technique_type type) = 0;

	virtual void set_input_layout(ss_render_input_layout* layout) = 0;

	virtual void set_vertex_buffer(
			size_t start,
			size_t num,
			ss_buffer* const * buffer,
			const unsigned int* strides,
			const unsigned int* offset
		) = 0;

	virtual void unset_vertex_buffer(
			size_t start,
			size_t num
		) = 0;

	virtual void set_ps_constant_buffer(
			size_t start,
			size_t num,
			ss_buffer* const * buffers
		) = 0;
	virtual void unset_ps_constant_buffer(
			size_t start,
			size_t num
		) = 0;

	virtual ss_texture2d* create_texture2d(
			size_t width, size_t height, 
			ss_render_format format, 
			const void* data) = 0;

	virtual void set_ps_texture2d_resource(
			size_t start,
			size_t num,
			ss_texture2d* const * textures
		) = 0;

	virtual void unset_ps_texture2d_resource(
		size_t start,
		size_t num
		) = 0;
};

typedef ss_render_device* (*ss_render_device_factory_type)(ss_render_device_type dt, uintptr_t hwnd);

