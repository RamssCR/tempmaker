cmake_minimum_required(VERSION 4.2)

set(REPROC_EXAMPLES OFF CACHE BOOL "" FORCE)
set(REPROC_TESTS OFF CACHE BOOL "" FORCE)
set(REPROC++ ON CACHE BOOL "" FORCE)

add_executable(App main.cpp)

target_link_libraries(App PRIVATE
    ftxui::ftxui
    nlohmann_json::nlohmann_json
    reproc++
)

target_include_directories(App PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_compile_options(App PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
    $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:-Wall -Wextra -Werror -Wpedantic>
)