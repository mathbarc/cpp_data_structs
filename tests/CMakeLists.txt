include_directories(${DATA_STRUCTURES_INCLUDE_DIR})

add_executable(linked_list_test
        ${CMAKE_CURRENT_SOURCE_DIR}/linked_list_test.cpp)
# target_link_libraries(linked_list_test data_structures gcov)
add_test(NAME linked_list_test COMMAND linked_list_test)

add_executable(double_linked_list_test
        ${CMAKE_CURRENT_SOURCE_DIR}/double_linked_list_test.cpp)
# target_link_libraries(double_linked_list_test data_structures)
add_test(NAME double_linked_list_test COMMAND double_linked_list_test)

add_executable(queue_test ${CMAKE_CURRENT_SOURCE_DIR}/queue_test.cpp)
# target_link_libraries(queue_test data_structures)
add_test(NAME queue_test COMMAND queue_test)

add_executable(circular_buffer_test
        ${CMAKE_CURRENT_SOURCE_DIR}/circular_buffer_test.cpp)
# target_link_libraries(circular_buffer_test data_structures)
add_test(NAME circular_buffer_test COMMAND circular_buffer_test)

add_executable(binary_tree_test
        ${CMAKE_CURRENT_SOURCE_DIR}/binary_tree_test.cpp)
# target_link_libraries(binary_tree_test data_structures)
add_test(NAME binary_tree_test COMMAND binary_tree_test)
