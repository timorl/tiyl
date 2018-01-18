cmake_minimum_required(VERSION 3.7)

include(FindPkgConfig)

project(tiyl)
set(tiyl_VERSION_MAJOR 0)
set(tiyl_VERSION_MINOR 0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -O0 -g")
set(CMAKE_CXX_FLAGS_RELEASE"${CMAKE_CXX_FLAGS} -O2")

add_library(stdc++fs UNKNOWN IMPORTED)
set_property(TARGET stdc++fs PROPERTY IMPORTED_LOCATION
	"/usr/lib/gcc/x86_64-pc-linux-gnu/6.4.0/libstdc++fs.a")

set(CMAKE_BUILD_TYPE "Debug")

set(CMAKE_DEBUG_POSTFIX "_d")

set(PROJECT_SOURCE_DIR ${CMAKE_CURRENT_BINARY_DIR}/src)
set(PROJECT_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/bin)
set(PROJECT_DOC_DIR ${CMAKE_CURRENT_BINARY_DIR}/doc)
set(PROJECT_DATA_DIR ${CMAKE_CURRENT_BINARY_DIR}/data)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})

set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_BINARY_DIR}/dist")

file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR})
file(MAKE_DIRECTORY ${PROJECT_DOC_DIR})
file(MAKE_DIRECTORY ${CMAKE_INSTALL_PREFIX})

set(COMMON_HDRS
	${PROJECT_SOURCE_DIR}/nlohmann/json.hpp
	${PROJECT_SOURCE_DIR}/projects/Project.hpp
	${PROJECT_SOURCE_DIR}/projects/Todo.hpp
	${PROJECT_SOURCE_DIR}/projects/Mess.hpp
	${PROJECT_SOURCE_DIR}/cli/Context.hpp
	${PROJECT_SOURCE_DIR}/cli/Commands.hpp
	${PROJECT_SOURCE_DIR}/cli/Cli.hpp
	)

set(COMMON_SRCS
	${PROJECT_SOURCE_DIR}/projects/Project.cpp
	${PROJECT_SOURCE_DIR}/projects/Todo.cpp
	${PROJECT_SOURCE_DIR}/projects/Mess.cpp
	${PROJECT_SOURCE_DIR}/cli/Context.cpp
	${PROJECT_SOURCE_DIR}/cli/Commands.cpp
	${PROJECT_SOURCE_DIR}/cli/Cli.cpp
	)

include_directories(
	${PROJECT_SOURCE_DIR}
	)

set(LIBS ${LIBS})

link_libraries(${LIBS} ${CMAKE_THREAD_LIBS_INIT})

add_executable(tiyl ${COMMON_HDRS} ${COMMON_SRCS} ${PROJECT_SOURCE_DIR}/tiyl.cpp)
target_link_libraries(${PROJECT_NAME} stdc++fs)
