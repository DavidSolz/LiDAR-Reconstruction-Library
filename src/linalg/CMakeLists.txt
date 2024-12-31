set(LIB_NAME lre-linalg)

add_library(${LIB_NAME}
    vector4.cpp
    matrix4.cpp
)

target_include_directories(${LIB_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include/linalg)

include(CheckCXXCompilerFlag)
check_cxx_compiler_flag("-mavx" COMPILER_SUPPORTS_AVX)

if(COMPILER_SUPPORTS_AVX)
    message(STATUS "AVX is supported by the compiler and will be enabled")
    target_compile_options(${LIB_NAME} PRIVATE -mavx)
else()
    message(STATUS "AVX is not supported by the compiler")
endif()