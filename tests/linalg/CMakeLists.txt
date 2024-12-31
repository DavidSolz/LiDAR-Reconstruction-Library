
file(GLOB_RECURSE TEST_SOURCES *.cpp)

add_executable(unit_tests ${TEST_SOURCES})

target_link_libraries(unit_tests
    PRIVATE
        LRE::linalg
        Catch2::Catch2WithMain
    )

catch_discover_tests(unit_tests)