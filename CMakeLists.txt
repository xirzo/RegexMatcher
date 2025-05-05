cmake_minimum_required(VERSION 3.30.5)

project(
  regex
  VERSION 1.0
  DESCRIPTION "My try on regex"
  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(bin)
add_subdirectory(lib)

option(BUILD_TESTS "Build tests" OFF)

if(BUILD_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()
