cmake_minimum_required(VERSION 4.2)

project(TempMaker VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

FetchContent_Declare(ftxui
    GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
    GIT_TAG v7.0.3
)

FetchContent_Declare(json
    GIT_REPOSITORY https://github.com/nlohmann/json
    GIT_TAG v3.12.0
)

FetchContent_Declare(reproc
    GIT_REPOSITORY https://github.com/DaanDeMeyer/reproc.git
    GIT_TAG v14.2.7
)

FetchContent_MakeAvailable(ftxui json reproc)

add_subdirectory(src)
