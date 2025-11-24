cmake_minimum_required(VERSION 3.5.0)
project(simulation VERSION 0.1.0 LANGUAGES C CXX)
cmake_policy(SET CMP0072 NEW)

find_package(OpenGL REQUIRED)

file(GLOB SRC_FILES
    src/*.cpp
    src/*.h
    src/*.c
    src/ODEsolver/*.h
    src/ODEsolver/*.cpp
)

add_executable(simulation ${SRC_FILES})

include_directories(simulation PRIVATE glm)

target_link_libraries(simulation
    glfw
    OpenGL::GL
)

#include(CTest)
#enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
