file(GLOB MEDIA_RETRIEVAL_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(
  file_reader_test ${MEDIA_RETRIEVAL_HEADERS}
                   ${CMAKE_CURRENT_SOURCE_DIR}/file_reader_test.cpp)
add_test(NAME file_reader_test
         COMMAND file_reader_test
                 ${CMAKE_CURRENT_SOURCE_DIR}/data/tv_packets.bin)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/data/tv_packets.bin
               ${CMAKE_CURRENT_BINARY_DIR}/data/ COPYONLY)
add_executable(media_retrieval ${MEDIA_RETRIEVAL_HEADERS}
                               ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)
add_test(NAME media_retrieval
         COMMAND media_retrieval
                 ${CMAKE_CURRENT_SOURCE_DIR}/data/tv_packets.bin)
