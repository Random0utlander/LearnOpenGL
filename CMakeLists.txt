cmake_minimum_required(VERSION 3.5.0)
project(my_first_simulation VERSION 0.1.0 LANGUAGES C CXX)
cmake_policy(SET CMP0072 NEW)

find_package(OpenGL REQUIRED)

add_executable(my_first_simulation 
    src/config.h
    src/main.cpp
    src/glad.c
    src/glad.h
    src/triangle_mesh.cpp
    src/shaders.h
    src/shaders.cpp
    src/stb_image.h
    src/textures.h
    src/textures.cpp
)

include_directories(my_first_simulation PRIVATE glm)

target_link_libraries(my_first_simulation
    glfw
    OpenGL::GL
)

#include(CTest)
#enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
