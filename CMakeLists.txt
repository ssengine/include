CMAKE_MINIMUM_REQUIRED(VERSION 3.1)

INCLUDE_DIRECTORIES($ENV{SS_INCLUDE_PATH})

SET(LOCAL_SOURCES_FILES
	ssengine/ssengine.h
	ssengine/ssengine.hpp
	ssengine/log.h
	ssengine/log.hpp

	ssengine/render/device.h
	ssengine/render/device.hpp)

ADD_LIBRARY(SSInclude
	STATIC
	${LOCAL_SOURCES_FILES}
)

SET_TARGET_PROPERTIES(SSInclude PROPERTIES LINKER_LANGUAGE CPP)