#pragma once

struct ss_color{
	float r, g, b, a;
};

enum ss_device_type{
	SS_DT_ANY		= 0xffffffff,

	SS_DT_NULL		= 0x0,
	SS_DT_SOFTWARE  = 0x1,

	SS_DT_OPENGL = 0x10,
	SS_DT_OPENGLES = 0x11,

	SS_DT_DIRECTX9 = 0x20,
	SS_DT_DIRECTX10 = 0x21,
	SS_DT_DIRECTX11 = 0x22,
	SS_DT_DIRECTX12 = 0x23
};

enum ss_clear_flags{
	SS_CF_NONE		= 0x0,
	SS_CF_COLOR		= 0x1,
	SS_CF_DEPTH		= 0x2,
	SS_CF_STENCIL	= 0x4
};

struct ss_render_device
{
	//TODO: CheckFeatureSupport
	//TODO: CheckFormatSupport
	
	virtual void clear_color(const ss_color& color) = 0;

	void clear_color(float r, float g, float b, float a){
		ss_color c = { r, g, b, a };
		clear_color(c);
	}
	
	virtual void clear(int flags = SS_CF_COLOR) = 0;
	virtual void present() = 0;

	virtual void destroy() = 0;
};

typedef ss_render_device* (*ss_device_factory_type)(ss_device_type dt, uintptr_t hwnd);
