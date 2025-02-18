cmake_minimum_required(VERSION 3.25)
project(cpp_data_structures VERSION 0.0.1)

add_subdirectory(data_structures)
add_subdirectory(problems)

include(CTest)
add_subdirectory(tests)
