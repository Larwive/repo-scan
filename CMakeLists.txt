cmake_minimum_required(VERSION 3.16)

project(repo-scan
    VERSION 0.1
    DESCRIPTION "Repository scanner."
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(repo-scan_lib
    src/orchestrator.cpp
)

set_target_properties(repo-scan_lib PROPERTIES
  POSITION_INDEPENDENT_CODE ON
)

target_compile_options(repo-scan_lib PRIVATE
    -Wall -Wextra -Wpedantic
)

target_include_directories(repo-scan_lib
    PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

add_executable(repo-scan
    src/main.cpp
)

target_link_libraries(repo-scan PRIVATE repo-scan_lib)
