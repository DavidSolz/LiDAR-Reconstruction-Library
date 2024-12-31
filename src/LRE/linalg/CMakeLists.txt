set(LIB_NAME lre-linalg)

add_library(${LIB_NAME}
    ${PROJECT_SOURCE_DIR}/src/LRE/linalg/vector4.cpp
    ${PROJECT_SOURCE_DIR}/src/LRE/linalg/matrix4.cpp
)

add_library(LRE::linalg ALIAS ${LIB_NAME})

target_include_directories(${LIB_NAME} 
    PUBLIC 
        ${PROJECT_SOURCE_DIR}/include
    PRIVATE 
        ${PROJECT_SOURCE_DIR}/src
)

include(CheckCXXCompilerFlag)
check_cxx_compiler_flag("-mavx" COMPILER_SUPPORTS_AVX)

if(COMPILER_SUPPORTS_AVX)
    message(STATUS "AVX is supported by the compiler and will be enabled")
    target_compile_options(${LIB_NAME} PRIVATE -mavx)
else()
    message(STATUS "AVX is not supported by the compiler")
endif()