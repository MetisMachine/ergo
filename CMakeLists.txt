cmake_minimum_required(VERSION 3.0)
project(ergo_dev)

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(CMAKE_MACOSX_RPATH 1)
endif()

set(EXECUTABLE_OUTPUT_PATH "bin")
set(BUILD_SHARED_LIBS NO)


set(CMAKE_CXX_STANDARD 11)

include(CheckIncludeFile)
include(CheckIncludeFileCXX)
include(CheckIncludeFiles)

if(NOT ${CMAKE_VERSION} LESS 3.2)
    set(CMAKE_CXX_STANDARD 11)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
else()
    message(STATUS "Checking compiler flags for C++11 support.")
    include(CheckCXXCompilerFlag)

    check_cxx_compiler_flag("-std=c++11" COMPILER_SUPPORTS_CXX11)
    check_cxx_compiler_flag("-std=c++0x" COMPILER_SUPPORTS_CXX0X)

    if(COMPILER_SUPPORTS_CXX11)
        message(STATUS "C++11 is supported.")

        if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -stdlib=libc++")
        else()
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
        endif()
    elseif(COMPILER_SUPPORTS_CXX0X)
        message(STATUS "C++0x is supported.")

        if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -stdlib=libc++")
        else()
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
        endif()
    else()
        message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
    endif()
endif()

set(LIB_SOURCES
    src/operation/operation.cpp
    src/operation/operation.h
    src/task/task.cpp
    src/task/task.h
    src/ergo.h
)

add_library(ergo STATIC ${LIB_SOURCES})
target_include_directories(ergo
    PUBLIC
    $(PROJECT_SOURCE_DIR)/src
)


set(SOURCE_FILES
    src/main.cpp
)

add_executable(ergo_dev ${SOURCE_FILES})
target_link_libraries(ergo_dev PRIVATE ergo)