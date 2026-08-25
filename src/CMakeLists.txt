cmake_minimum_required(VERSION 4.2)

set(BOOST_ENABLE_CMAKE ON CACHE BOOL "" FORCE)

add_library(ScaffolderLib STATIC
    utils/package_manager.cpp
    ui/wizard.cpp
)

target_include_directories(ScaffolderLib PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(ScaffolderLib
    PRIVATE nlohmann_json::nlohmann_json
    PUBLIC ftxui::ftxui Boost::process
)

add_executable(App main.cpp)
target_link_libraries(App PRIVATE ScaffolderLib)

target_compile_options(App PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
    $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:-Wall -Wextra -Werror -Wpedantic>
)