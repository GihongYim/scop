cmake_minimum_required(VERSION 3.13)

set(PROJECT_NAME scop)
set(CMAKE_CXX_STANDARD 17)

project(${PROJECT_NAME})
add_executable(${PROJECT_NAME} src/main.cpp)

set(WINDOW_NAME "Hello, OpenGL!")
set(WINDOW_WIDTH 960)
set(WINDOW_HEIGHT 540)

include(Dependency.cmake)

target_include_directories(${PROJECT_NAME} PUBLIC ${DEP_INCLUDE_DIR})
target_link_directories(${PROJECT_NAME} PUBLIC ${DEP_LIB_DIR})
target_link_libraries(${PROJECT_NAME} PUBLIC ${DEP_LIBS})

add_dependencies(${PROJECT_NAME} ${DEP_LIST})

