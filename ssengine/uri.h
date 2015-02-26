#pragma once

#include <ssengine/ssengine.h>
#include <ssengine/core.h>

#ifdef __cplusplus
#include <string>

struct ss_uri{
	ss_core_context* C;

	std::string schema;
	std::string user;
	std::string password;
	std::string host;
	std::string path;
	std::string search;
	std::string tag;
	int			port;

	ss_uri(ss_core_context* _C) :C(_C){}

	SS_CORE_API std::string str() const;

	SS_CORE_API static ss_uri parse(ss_core_context* C, const std::string& uri);
	SS_CORE_API static ss_uri from_file(ss_core_context* C, const char* path);

	//methods 
	ss_uri join(const char* uri) const{
		return join(ss_uri::parse(C, uri));
	}
	SS_CORE_API ss_uri join(const ss_uri& other) const;
	SS_CORE_API void normalize();
	SS_CORE_API ss_uri base_dir() const;

	SS_CORE_API bool is_local() const;

	// queries
	SS_CORE_API bool exists() const;
	SS_CORE_API bool is_file() const;
	SS_CORE_API bool is_directory() const;
	SS_CORE_API struct input_stream*  open_for_read() const;

	//TODO: remove dir

	// operates
	SS_CORE_API bool mkdir() const;
	SS_CORE_API struct output_stream*  open_for_write() const;
	SS_CORE_API struct output_stream*  open_for_append() const;
};

#else
typedef struct ss_uri ss_uri;
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

typedef struct ss_uri_schema_handler
{
	virtual ~ss_uri_schema_handler(){}

	// properties
	virtual bool is_local() = 0;

	// queries
	virtual bool exists(const ss_uri& uri) = 0;
	virtual bool is_file(const ss_uri& uri) = 0;
	virtual bool is_directory(const ss_uri& uri) = 0;
	virtual struct input_stream*  open_for_read(const ss_uri& uri) = 0;

	//TODO: remove dir

	// operates
	virtual bool mkdir(const ss_uri& uri) = 0;
	virtual struct output_stream*  open_for_write(const ss_uri& uri) = 0;
	virtual struct output_stream*  open_for_append(const ss_uri& uri) = 0;
} ss_uri_schema_handler;

#else
struct input_stream;
struct output_stream;

typedef struct ss_uri_schema_handler ss_uri_schema_handler;
#endif

#ifdef __cplusplus
extern "C"{
#endif

#include <stdbool.h>

SS_CORE_API void ss_uri_add_schema(ss_core_context* C, const char* schema, ss_uri_schema_handler* handler);

SS_CORE_API void ss_uri_add_schema_alias(ss_core_context* C, const char* schema, const ss_uri& alias, bool readOnly = false);

//TODO: provide C++ interface for theses:

SS_CORE_API bool ss_uri_exists(ss_core_context* C, const char* uri);
SS_CORE_API bool ss_uri_is_file(ss_core_context* C, const char* uri);
SS_CORE_API bool ss_uri_is_directory(ss_core_context* C, const char* uri);
SS_CORE_API bool ss_uri_mkdir(ss_core_context* C, const char* uri);

SS_CORE_API input_stream* ss_uri_open_for_read(ss_core_context* C, const char* uri);
SS_CORE_API output_stream* ss_uri_open_for_write(ss_core_context* C, const char* uri);
SS_CORE_API output_stream* ss_uri_open_for_append(ss_core_context* C, const char* uri);


#ifdef __cplusplus
}
#endif
