if(CMAKE_HOST_WIN32)
    cmake_minimum_required(VERSION 3.24)
else()
    cmake_minimum_required(VERSION 3.22)
endif()

project(LRE VERSION 1.0)

set(LIB_NAME lre)

add_library(${LIB_NAME}
    src/vector4.cpp
    src/matrix4.cpp
)

target_include_directories(${LIB_NAME} PUBLIC include)

include(CheckCXXCompilerFlag)
check_cxx_compiler_flag("-mavx" COMPILER_SUPPORTS_AVX)

if(COMPILER_SUPPORTS_AVX)
    message(STATUS "AVX is supported by the compiler and will be enabled")
    target_compile_options(${LIB_NAME} PRIVATE -mavx)
else()
    message(STATUS "AVX is not supported by the compiler")
endif()