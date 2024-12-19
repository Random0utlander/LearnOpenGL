cmake_minimum_required(VERSION 3.5.0)
project(my_first_simulation VERSION 0.1.0 LANGUAGES C CXX)
cmake_policy(SET CMP0072 NEW)

find_package(OpenGL REQUIRED)

add_executable(my_first_simulation 
    src/config.h
    src/main.cpp
    src/glad.c
    src/glad.h
    src/shaderClass.h
    src/shaderClass.cpp
    src/VAO.h
    src/VAO.cpp
    src/VBO.h
    src/VBO.cpp
    src/EBO.cpp
    src/EBO.h
)

include_directories(my_first_simulation PRIVATE glm)

target_link_libraries(my_first_simulation
    glfw
    OpenGL::GL
)

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
