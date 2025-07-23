cmake_minimum_required(VERSION 3.24)

project(
  TopTracker
  VERSION 1.0
  LANGUAGES CXX
)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)

find_program(CLANG_TIDY_EXE NAMES clang-tidy-12 clang-tidy-10 clang-tidy)
if (NOT CLANG_TIDY_EXE)
  message(WARNING "clang-tidy not found")
else()
  execute_process(
    COMMAND ${CLANG_TIDY_EXE} --version
    OUTPUT_VARIABLE CLANG_TIDY_VERSION)
  message("clang-tidy found:\n" ${CLANG_TIDY_VERSION})
endif()

enable_testing()

include_directories(src/TopTracker)
include_directories(ext/GTest)

add_subdirectory(ext)
add_subdirectory(src)