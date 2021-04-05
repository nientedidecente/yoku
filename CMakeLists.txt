cmake_minimum_required(VERSION 3.16)

project(yoku)
set(CMAKE_CXX_STANDARD 17)


# SFML Lib installed with apt-get install sfml-dev
find_package(SFML 2.5 COMPONENTS audio graphics window system REQUIRED)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

# the -I flag in compiler
include_directories(
  ${PROJECT_SOURCE_DIR}/include/
)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib") 
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

set(YOKU_LIB_SOURCES 
  include/yoku/Assets.cpp
  include/yoku/SceneManager.cpp
  include/yoku/Window.cpp
  include/yoku/Game.cpp
)
set(YOKU_LIBRARY_NAME yoku)
add_library(${YOKU_LIBRARY_NAME} STATIC SHARED ${YOKU_LIB_SOURCES})

#add_compile_definitions(FPS=1)
message("Build Type: " ${CMAKE_BUILD_TYPE})
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
  add_compile_definitions(DEBUG)
endif()


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(PONG_EXAMPLE_SOURCES 
  examples/pong/src/main.cpp
  examples/pong/src/scenes/Main.cpp
  examples/pong/src/scenes/Splash.cpp
  examples/pong/src/Pong.cpp
)
file(COPY examples/pong/src/assets DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
add_executable(pong ${PONG_EXAMPLE_SOURCES})
target_link_libraries(pong sfml-audio sfml-graphics sfml-window sfml-system ${YOKU_LIBRARY_NAME})