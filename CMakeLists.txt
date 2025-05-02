cmake_minimum_required(VERSION 3.25)
project(cpp_data_structures VERSION 0.0.1)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  set(ENABLE_COVERAGE
      ON
      CACHE BOOL "Enable test coverage")

  if(ENABLE_COVERAGE)
    # set compiler flags
    set(CMAKE_CXX_FLAGS_DEBUG
        "-g -O0 -coverage"
        CACHE STRING "" FORCE)

    # find required tools
    find_program(LCOV lcov REQUIRED)
    find_program(GENHTML genhtml REQUIRED)

    # add coverage target
    add_custom_target(
      coverage
      # gather data
      COMMAND ${LCOV} --directory ${CMAKE_CURRENT_SOURCE_DIR} --capture
              --initial --output-file baseline_coverage.info --no-external
      COMMAND ${LCOV} --directory ${CMAKE_CURRENT_SOURCE_DIR} --capture
              --output-file coverage.info --no-external
      COMMAND ${LCOV} --add-tracefile baseline_coverage.info --add-tracefile
              coverage.info --output-file coverage.info
      # generate report
      COMMAND ${GENHTML} --demangle-cpp -o coverage coverage.info
      WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
  endif()
endif()

include(CTest)
add_subdirectory(data_structures)
add_subdirectory(problems)

add_subdirectory(tests)
