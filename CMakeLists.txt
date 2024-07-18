CMAKE_MINIMUM_REQUIRED(VERSION 3.27)
PROJECT(RSP
	DESCRIPTION "Graph Library in C++"
	VERSION 0.1
	LANGUAGES CXX
)

SET(CMAKE_CXX_STANDARD 23)

SET(rsp_sources
	include/IGraph.h
	include/Graph_AdjacencyList.h
	include/GraphBuilder.h
	include/BFS.h
	include/Dijkstra.h
)

# Fetch yaml-cpp
include(FetchContent)

FetchContent_Declare(
	yaml-cpp
	GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
	GIT_TAG master # Can be a tag (yaml-cpp-x.x.x), a commit hash, or a branch name (master)
)
FetchContent_GetProperties(yaml-cpp)

if(NOT yaml-cpp_POPULATED)
	message(STATUS "Populating yaml-cpp...")
	FetchContent_Populate(yaml-cpp)
	SET(YAML_CPP_BUILD_TESTS OFF)
	ADD_SUBDIRECTORY(${yaml-cpp_SOURCE_DIR} ${yaml-cpp_BINARY_DIR})
	MESSAGE(STATUS "Done.")
endif()

MESSAGE(STATUS ${YAML_CPP_BUILD_TESTS})

ADD_LIBRARY(${PROJECT_NAME} STATIC ${rsp_sources})
SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
TARGET_INCLUDE_DIRECTORIES(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
TARGET_LINK_LIBRARIES(${PROJECT_NAME} PUBLIC yaml-cpp::yaml-cpp) # The library or executable that require yaml-cpp library

ADD_EXECUTABLE(example targets/example.cc)
TARGET_LINK_LIBRARIES(example PRIVATE ${PROJECT_NAME})