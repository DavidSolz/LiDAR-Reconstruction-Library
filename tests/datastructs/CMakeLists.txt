
file(GLOB_RECURSE TEST_SOURCES *.cpp)

add_executable(unit_datastructs_tests ${TEST_SOURCES})

target_link_libraries(unit_datastructs_tests
    PRIVATE
        LRE::linalg
        LRE::datastructs
        Catch2::Catch2WithMain
    )

catch_discover_tests(unit_datastructs_tests)
