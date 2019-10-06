
include(ExternalProject)

ExternalProject_Add(
	iniparser
	GIT_REPOSITORY https://github.com/ndevilla/iniparser
	# GIT_TAG				 v4.1
	GIT_SHALLOW		 1
	GIT_PROGRESS	 1
	BUILD_IN_SOURCE 1
	CONFIGURE_COMMAND ""
	BUILD_COMMAND make
	INSTALL_COMMAND ""
	TEST_COMMAND make check
	COMMAND  ${CMAKE_COMMAND} -E copy_if_different "<SOURCE_DIR>/src/iniparser.h"
		"${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/iniparser/inc"
	COMMAND  ${CMAKE_COMMAND} -E copy_if_different "<SOURCE_DIR>/src/dictionary.h"
		"${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/iniparser/inc"
	COMMAND  ${CMAKE_COMMAND} -E copy_if_different "<SOURCE_DIR>/libiniparser.a"
		"${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/iniparser/lib"
	COMMAND  ${CMAKE_COMMAND} -E copy_if_different "<SOURCE_DIR>/libiniparser.so.1"
		"${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/iniparser/lib"
	)
