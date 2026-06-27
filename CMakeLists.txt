cmake_minimum_required(VERSION 3.16)

project(repo-scan
    VERSION 0.1
    DESCRIPTION "Repository scanner."
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

FetchContent_Declare(
  nlohmann_json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG        v3.11.3
)

FetchContent_MakeAvailable(nlohmann_json)

add_library(repo-scan_lib
    src/orchestrator.cpp
)

set_target_properties(repo-scan_lib PROPERTIES
  POSITION_INDEPENDENT_CODE ON
)

target_compile_options(repo-scan_lib PRIVATE
    -Wall -Wextra -Wpedantic -Werror
)

target_include_directories(repo-scan_lib
    PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

add_executable(repo-scan
    src/main.cpp
)

target_compile_options(repo-scan PRIVATE
    -Wall -Wextra -Wpedantic -Werror
)

target_link_libraries(repo-scan_lib
  PUBLIC
    nlohmann_json::nlohmann_json
)

target_link_libraries(repo-scan PRIVATE repo-scan_lib)

option(BUILD_TESTS "Build tests" OFF)

if(BUILD_TESTS)
  FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.14.0
  )
  FetchContent_MakeAvailable(googletest)

  enable_testing()

  add_executable(repo_scan_tests
    tests/test_orchestrator.cpp
  )
  target_link_libraries(repo_scan_tests
    PRIVATE repo-scan_lib GTest::gtest_main
  )

  target_compile_options(repo_scan_tests PRIVATE
    -Wall -Wextra -Wpedantic -Werror
)

  include(GoogleTest)
  gtest_discover_tests(repo_scan_tests)
endif()
