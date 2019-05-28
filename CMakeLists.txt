cmake_minimum_required(VERSION 3.8)

project(snakegame VERSION 0.1 DESCRIPTION "a simple snake game")

# Use C++11 standard for compiling
set(CMAKE_CXX_STANDARD 11)

# Find SFML library
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Choose dynamic or static linking of SFML
if(WIN32)
    option(SFML_STATIC_LIBRARIES "Build the executable with static linking" OFF)
endif(WIN32)

# Bring source files in src/ directory into the project
set(SOURCE_FILES src/apple.cpp src/game.cpp src/main.cpp src/snake.cpp
    src/wall.cpp src/window.cpp src/world.cpp src/event_manager.cpp
    src/message_box.cpp)

# Bring header files in include/ directory into the project
set(HEADER_FILES include/apple.h include/game.h include/snake.h
    include/wall.h include/window.h include/world.h include/event_manager.h
    include/message_box.h)

# Add all sources to target
add_executable(snakegame ${SOURCE_FILES} ${HEADER_FILES})

# Add paths to includes
target_include_directories(snakegame PUBLIC include)

# Linking
target_link_libraries(snakegame sfml-graphics sfml-window sfml-system)

