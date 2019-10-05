# All the source files for the bot.
file(GLOB SOURCES "*.cpp")

include_directories(${CMAKE_SOURCE_DIR}/inc)

if (CURL_FOUND)
	include_directories(SYSTEM "${CURL_INCLUDE_DIRS}")
endif ()

if (GLOG_FOUND)
	include_directories(SYSTEM "${GLOG_INCLUDE_DIRS}")
endif ()

if (RAPIDJSON_INCLUDE_DIRS)
	include_directories(SYSTEM "${RAPIDJSON_INCLUDE_DIRS}")
endif ()

# Show more warnings at compiletime.
if (MSVC)
    # FIXME: put Windows specific options here.
else ()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
endif ()

# Set ExecutableName.
add_executable(pocket_download ${SOURCES})

target_link_libraries(pocket_download curlpp)

if (CURL_FOUND)
	target_link_libraries(pocket_download ${CURL_LIBRARIES})
endif ()

if (GLOG_FOUND)
	target_link_libraries(pocket_download ${GLOG_LIBRARIES})
endif ()

if (APPLE)
	target_link_libraries(pocket_download "-framework Carbon")
endif ()

# Linux specific.
if (UNIX AND NOT APPLE)
	target_link_libraries(pocket_download pthread dl)
endif ()
