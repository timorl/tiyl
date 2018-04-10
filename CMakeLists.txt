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
	${PROJECT_SOURCE_DIR}/util/Dates.hpp
	${PROJECT_SOURCE_DIR}/util/Config.hpp
	${PROJECT_SOURCE_DIR}/projects/Project.hpp
	${PROJECT_SOURCE_DIR}/projects/Action.hpp
	${PROJECT_SOURCE_DIR}/projects/Habit.hpp
	${PROJECT_SOURCE_DIR}/projects/Event.hpp
	${PROJECT_SOURCE_DIR}/projects/Annual.hpp
	${PROJECT_SOURCE_DIR}/projects/Mess.hpp
	${PROJECT_SOURCE_DIR}/database/Files.hpp
	${PROJECT_SOURCE_DIR}/cli/Pretty.hpp
	${PROJECT_SOURCE_DIR}/cli/Utils.hpp
	${PROJECT_SOURCE_DIR}/cli/Context.hpp
	${PROJECT_SOURCE_DIR}/cli/Movement.hpp
	${PROJECT_SOURCE_DIR}/cli/Mess.hpp
	${PROJECT_SOURCE_DIR}/cli/Annual.hpp
	${PROJECT_SOURCE_DIR}/cli/Event.hpp
	${PROJECT_SOURCE_DIR}/cli/Habit.hpp
	${PROJECT_SOURCE_DIR}/cli/Action.hpp
	${PROJECT_SOURCE_DIR}/cli/Project.hpp
	${PROJECT_SOURCE_DIR}/cli/Dep.hpp
	${PROJECT_SOURCE_DIR}/cli/All.hpp
	${PROJECT_SOURCE_DIR}/cli/Status.hpp
	${PROJECT_SOURCE_DIR}/cli/Commands.hpp
	${PROJECT_SOURCE_DIR}/cli/Cli.hpp
	)

set(COMMON_SRCS
	${PROJECT_SOURCE_DIR}/util/Dates.cpp
	${PROJECT_SOURCE_DIR}/util/Config.cpp
	${PROJECT_SOURCE_DIR}/projects/Project.cpp
	${PROJECT_SOURCE_DIR}/projects/Action.cpp
	${PROJECT_SOURCE_DIR}/projects/Habit.cpp
	${PROJECT_SOURCE_DIR}/projects/Event.cpp
	${PROJECT_SOURCE_DIR}/projects/Annual.cpp
	${PROJECT_SOURCE_DIR}/projects/Mess.cpp
	${PROJECT_SOURCE_DIR}/database/Files.cpp
	${PROJECT_SOURCE_DIR}/cli/Pretty.cpp
	${PROJECT_SOURCE_DIR}/cli/Utils.cpp
	${PROJECT_SOURCE_DIR}/cli/Context.cpp
	${PROJECT_SOURCE_DIR}/cli/Movement.cpp
	${PROJECT_SOURCE_DIR}/cli/Mess.cpp
	${PROJECT_SOURCE_DIR}/cli/Annual.cpp
	${PROJECT_SOURCE_DIR}/cli/Event.cpp
	${PROJECT_SOURCE_DIR}/cli/Habit.cpp
	${PROJECT_SOURCE_DIR}/cli/Action.cpp
	${PROJECT_SOURCE_DIR}/cli/Project.cpp
	${PROJECT_SOURCE_DIR}/cli/Dep.cpp
	${PROJECT_SOURCE_DIR}/cli/All.cpp
	${PROJECT_SOURCE_DIR}/cli/Status.cpp
	${PROJECT_SOURCE_DIR}/cli/Cli.cpp
	)

include_directories(
	${PROJECT_SOURCE_DIR}
	)

set(LIBS ${LIBS})

link_libraries(${LIBS} ${CMAKE_THREAD_LIBS_INIT})

add_executable(tiyl ${COMMON_HDRS} ${COMMON_SRCS} ${PROJECT_SOURCE_DIR}/tiyl.cpp)
target_link_libraries(${PROJECT_NAME} stdc++fs)

#Catch for tests
set(CATCH_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/catch)
add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE ${CATCH_INCLUDE_DIR})

set(TEST_SOURCES
	${PROJECT_SOURCE_DIR}/util/tests/Dates.cpp
	)
add_executable(tests ${COMMON_HDRS} ${COMMON_SRCS} ${TEST_SOURCES} ${PROJECT_SOURCE_DIR}/tests.cpp)
target_link_libraries(tests Catch stdc++fs)
