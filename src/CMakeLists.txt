cmake_minimum_required(VERSION 4.2)

add_executable(App main.cpp)

target_include_directories(App PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_compile_options(App PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
    $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:-Wall -Wextra -Werror -Wpedantic>
)