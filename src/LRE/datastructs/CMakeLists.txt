set(LIB_NAME lre-datastructs)

add_library(${LIB_NAME}
    ${PROJECT_SOURCE_DIR}/src/LRE/datastructs/hash_grid.cpp
)

add_library(LRE::datastructs ALIAS ${LIB_NAME})

target_include_directories(${LIB_NAME}
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
    PRIVATE
        ${PROJECT_SOURCE_DIR}/src
)
