cmake_minimum_required(VERSION 3.13)

set(PROJECT_NAME scop)
set(CMAKE_CXX_STANDARD 17)

if (APPLE)
	set(CMAKE_CXX_FLAGS "-framework Cocoa -framework IOKit -framework OpenGL")
endif()


set(WINDOW_NAME "Hello, Scop")
set(WINDOW_WIDTH 960)
set(WINDOW_HEIGHT 540)

project(${PROJECT_NAME})
add_executable(${PROJECT_NAME}
	src/main.cpp
	src/common.cpp src/common.h
	src/shader.cpp src/shader.h
	src/program.cpp src/program.h
	src/context.cpp src/context.h
	src/buffer.cpp src/buffer.h
	src/vertex_layout.cpp src/vertex_layout.h
	)

include(Dependency.cmake)

target_include_directories(${PROJECT_NAME} PUBLIC ${DEP_INCLUDE_DIR})
target_link_directories(${PROJECT_NAME} PUBLIC ${DEP_LIB_DIR})
target_link_libraries(${PROJECT_NAME} PUBLIC ${DEP_LIBS})

target_compile_definitions(${PROJECT_NAME} PUBLIC
	WINDOW_NAME="${WINDOW_NAME}"
	WINDOW_WIDTH=${WINDOW_WIDTH}
	WINDOW_HEIGHT=${WINDOW_HEIGHT}
)

add_dependencies(${PROJECT_NAME} ${DEP_LIST})

