cmake_minimum_required(VERSION 3.16)
project(GameEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Find GLFW
find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

# Add source files
add_executable(GameEngine src/main.cpp)

# Link libraries
target_link_libraries(GameEngine glfw OpenGL::GL)


