cmake_minimum_required(VERSION 4.2)

add_executable(Tests
    examples.cc
    utils/package_manager.cc
)

target_include_directories(Tests PUBLIC ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(Tests
    PRIVATE GTest::gtest_main GTest::gmock_main ScaffolderLib
)
include(GoogleTest)

gtest_discover_tests(Tests)