
FIND_PACKAGE(OpenCV COMPONENTS core highgui imgcodecs imgproc REQUIRED)


file(GLOB GAME_OF_LIFE_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/game_of_life/*.cpp)
message(${CMAKE_CURRENT_SOURCE_DIR}/game_of_life/*.cpp)
add_executable(game_of_life ${GAME_OF_LIFE_SOURCES})
target_link_libraries(game_of_life ${OpenCV_LIBRARIES})

