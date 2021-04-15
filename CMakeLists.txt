cmake_minimum_required(VERSION 3.16)

project(yoku)
set(CMAKE_CXX_STANDARD 17)


# SFML Lib installed with apt-get install sfml-dev
find_package(SFML 2.5 COMPONENTS audio graphics window system REQUIRED)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

# the -I flag in compiler
include_directories(
  ${PROJECT_SOURCE_DIR}/src/include/
)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib") 
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

set(YOKU_LIB_SOURCES 
  src/Assets.cpp
  src/SceneManager.cpp
  src/Window.cpp
  src/Game.cpp
  src/rng.cpp
  )
  set(YOKU_LIBRARY_NAME yoku)
  add_library(${YOKU_LIBRARY_NAME}.static STATIC ${YOKU_LIB_SOURCES})
  add_library(${YOKU_LIBRARY_NAME} SHARED ${YOKU_LIB_SOURCES})
  file(COPY src/include DESTINATION ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

#add_compile_definitions(FPS=1)
message("Build Type: " ${CMAKE_BUILD_TYPE})
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
  add_compile_definitions(DEBUG)
endif()


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(PONG_EXAMPLE_SOURCES 
  examples/pong/src/main.cpp
  examples/pong/src/entities/PlayerPaddle.cpp
  examples/pong/src/entities/CpuPaddle.cpp
  examples/pong/src/entities/Ball.cpp
  examples/pong/src/entities/Paddle.cpp
  examples/pong/src/scenes/Main.cpp
  examples/pong/src/scenes/Splash.cpp
  examples/pong/src/Pong.cpp
  )
  file(COPY examples/pong/src/assets DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
  add_executable(pong ${PONG_EXAMPLE_SOURCES})
  target_link_libraries(pong sfml-graphics sfml-window ${YOKU_LIBRARY_NAME})
  
  set(SIMULATION_EXAMPLE_SOURCES 
  examples/simulation/src/main.cpp
  examples/simulation/src/entities/Cell.cpp
  examples/simulation/src/scenes/Main.cpp
  examples/simulation/src/scenes/Splash.cpp
  examples/simulation/src/Simulation.cpp
)
file(COPY examples/simulation/src/assets DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
add_executable(simulation ${SIMULATION_EXAMPLE_SOURCES})
target_link_libraries(simulation sfml-graphics sfml-window ${YOKU_LIBRARY_NAME})
