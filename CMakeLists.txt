cmake_minimum_required(VERSION 3.16)
project(CustomGameEngine)

set(CMAKE_CXX_STANDARD 17)

# === Directory Setup ===
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(ENGINE_DIR ${CMAKE_SOURCE_DIR}/engine)
set(EXTERNAL_DIR ${CMAKE_SOURCE_DIR}/external)
set(GLAD_DIR ${EXTERNAL_DIR}/glad)

# === GLAD ===
file(GLOB GLAD_SOURCES ${GLAD_DIR}/src/*.c)
include_directories(${GLAD_DIR}/include)

# === Includes ===
include_directories(${ENGINE_DIR})
include_directories(${CMAKE_SOURCE_DIR}) # Includes src/
include_directories(${EXTERNAL_DIR})

# === Dependencies ===
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# === Engine Sources ===

# --- 2D Engine Sources ---
file(GLOB_RECURSE ENGINE_2D_SOURCES
    ${ENGINE_DIR}/core/*.cpp
    ${ENGINE_DIR}/scene/*.cpp
    ${ENGINE_DIR}/physics/Particle.cpp
    ${ENGINE_DIR}/physics/Constraint2D.cpp
    ${ENGINE_DIR}/objects/Ball2D.cpp
    ${ENGINE_DIR}/objects/Cloth2D.cpp
)

# --- 3D Engine Sources ---
file(GLOB_RECURSE ENGINE_3D_SOURCES
    ${ENGINE_DIR}/core/*.cpp
    ${ENGINE_DIR}/scene/*.cpp
    ${ENGINE_DIR}/graphics/*.cpp
    ${ENGINE_DIR}/physics/Particle3D.cpp
    ${ENGINE_DIR}/physics/Constraint3D.cpp
    ${ENGINE_DIR}/objects/Ball3D.cpp
    ${ENGINE_DIR}/objects/Cloth3D.cpp   # ✅ Ensure this is listed
)

# === Executable: 2D ===
add_executable(main2D
    ${SRC_DIR}/main2D.cpp
    ${ENGINE_2D_SOURCES}
)

target_link_libraries(main2D
    sfml-graphics
    sfml-window
    sfml-system
)

# === Executable: 3D ===
add_executable(main3D
    ${SRC_DIR}/main3D.cpp
    ${ENGINE_3D_SOURCES}
    ${GLAD_SOURCES}
)

target_link_libraries(main3D
    ${OPENGL_LIBRARIES}
    glfw
    sfml-system
)
