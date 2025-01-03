include(FetchContent)

FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.7.0
    GIT_SHALLOW ON
    )

FetchContent_MakeAvailable(Catch2)

enable_testing()
include(Catch)

target_compile_features(Catch2 PRIVATE cxx_std_17)

add_subdirectory(linalg)
add_subdirectory(datastructs)
