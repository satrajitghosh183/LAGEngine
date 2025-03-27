# cmake_minimum_required(VERSION 3.16)
# project(GameEngine)

# set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
# include_directories(${PROJECT_SOURCE_DIR}/include)

# file(GLOB SRC_FILES "${PROJECT_SOURCE_DIR}/src/*.cpp")

# add_executable(GameEngine ${SRC_FILES})
# target_link_libraries(GameEngine sfml-graphics sfml-window sfml-system)
# # cmake_minimum_required(VERSION 3.16)
# # project(GameEngine)

# # set(CMAKE_CXX_STANDARD 17)
# # set(CMAKE_CXX_STANDARD_REQUIRED ON)
# # set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# # # Find required packages.
# # find_package(glfw3 REQUIRED)
# # find_package(GLEW REQUIRED)
# # find_package(glm REQUIRED)
# # find_package(OpenGL REQUIRED)

# # include_directories(${PROJECT_SOURCE_DIR}/include)

# # # Only add the new 3D files and main.cpp, Camera3D.cpp, Shader.cpp
# # file(GLOB NEW_SRC_FILES 
# #     "${PROJECT_SOURCE_DIR}/src/*3D.cpp" 
# #     "${PROJECT_SOURCE_DIR}/src/main.cpp" 
# #     "${PROJECT_SOURCE_DIR}/src/Camera3D.cpp"
# #     "${PROJECT_SOURCE_DIR}/src/Shader.cpp"
# # )

# # add_executable(GameEngine ${NEW_SRC_FILES})
# # target_link_libraries(GameEngine glfw GLEW::GLEW glm::glm OpenGL::GL)

