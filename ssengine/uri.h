#pragma once

#include <ssengine/ssengine.h>

#ifdef __cplusplus
#include <UriParser.hpp>
typedef network::uri ss_uri;
#else
typedef struct uri ss_uri;
#endif

#ifdef __cplusplus

#include <stdio.h>
struct basic_stream {
	virtual void close() = 0;

	virtual bool seek(long long offset, long origin) = 0;
	virtual long long tell() = 0;
};

struct input_stream : basic_stream {
	virtual size_t read(void* buf, size_t size) = 0;
};

struct output_stream : basic_stream {
	virtual size_t write(const void* buf, size_t size) = 0;
};
#else
struct input_stream;
struct output_stream;
#endif

#ifdef __cplusplus
extern "C"{
#endif

#include <stdbool.h>

typedef struct ss_uri_schema_handler
{
	// properties
	bool (*is_local)();

	// queries
	bool(*exists)(const ss_uri& uri);
	bool(*is_file)(const ss_uri& uri);
	bool(*is_directory)(const ss_uri& uri);
	struct input_stream* (*open_for_read)(const ss_uri& uri);

	//TODO: remove dir

	// operates
	bool(*mkdir)(const ss_uri& uri);
	struct output_stream* (*open_for_write)(const ss_uri& uri);
	struct output_stream* (*open_for_append)(const ss_uri& uri);
} ss_uri_schema_handler;

SS_CORE_API void ss_uri_add_schema(const char* schema, ss_uri_schema_handler handler);

SS_CORE_API void ss_uri_init_schemas();

//TODO: provide C++ interface for theses:

SS_CORE_API bool ss_uri_exists(const char* uri);
SS_CORE_API bool ss_uri_is_file(const char* uri);
SS_CORE_API bool ss_uri_is_directory(const char* uri);
SS_CORE_API bool ss_uri_mkdir(const char* uri);

SS_CORE_API input_stream* ss_uri_open_for_read(const char* uri);
SS_CORE_API output_stream* ss_uri_open_for_write(const char* uri);
SS_CORE_API output_stream* ss_uri_open_for_append(const char* uri);


#ifdef __cplusplus
}
#endif
