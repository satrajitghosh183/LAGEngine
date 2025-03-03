cmake_minimum_required(VERSION 3.16)
project(GameEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set output directories for binaries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Add the source directory
add_executable(GameEngine src/main.cpp)

# Cross-platform linking
if(WIN32)
    target_link_libraries(GameEngine opengl32)
elseif(APPLE)
    find_library(COCOA_LIBRARY Cocoa)
    target_link_libraries(GameEngine ${COCOA_LIBRARY})
elseif(UNIX)
    target_link_libraries(GameEngine GL X11)
endif()
