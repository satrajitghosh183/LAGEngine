add_executable(imgui_sfml_example_multiple_windows main.cpp)
target_link_libraries(imgui_sfml_example_multiple_windows PRIVATE ImGui-SFML::ImGui-SFML)
target_compile_options(imgui_sfml_example_multiple_windows PRIVATE ${IMGUI_SFML_WARNINGS})
