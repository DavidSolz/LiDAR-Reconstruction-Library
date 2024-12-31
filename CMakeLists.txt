if(CMAKE_HOST_WIN32)
    cmake_minimum_required(VERSION 3.24)
else()
    cmake_minimum_required(VERSION 3.22)
endif()

project(LRE VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_COLOR_DIAGNOSTICS ON)

add_subdirectory(extern)
add_subdirectory(src)
add_subdirectory(tests)