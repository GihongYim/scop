include(ExternalProject)

# Dependency 관련 변수 설정
set(DEP_INSTALL_DIR ${PROJECT_BINARY_DIR}/install)
set(DEP_INCLUDE_DIR ${DEP_INSTALL_DIR}/include)
set(DEP_LIB_DIR ${DEP_INSTALL_DIR}/lib)

ExternalProject_Add(
	dep-spdlog
	GIT_REPOSITORY "https://github.com/gabime/spdlog.git"
	GIT_TAG "v1.x"
	GIT_SHALLOW 1
	UPDATE_COMMAND "" TEST_COMMAND "" PATCH_COMMAND ""
	CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${DEP_INSTALL_DIR}
	)

set(DEP_LIST ${DEP_LIST} dep-spdlog)
set(DEP_LIBS ${DEP_LIBS} spdlog$<$<CONFIG:Debug>:d>)

set(DEP_INSTALL_DIR ${PROJECT_BINARY_DIR}/install)
set(DEP_INCLUDE_DIR ${DEP_INSTALL_DIR}/include)
set(DEP_LIB_DIR ${DEP_INSTALL_DIR}/lib)

ExternalProject_Add(
	dep_glfw
	GIT_REPOSITORY "https://github.com/glfw/glfw.git"
	GIT_TAG "3.3.2"
	GIT_SHALLOW 1
	UPDATE_COMMAND "" PATCH_COMMAND "" TEST_COMMAND ""
	CMAKE_ARGS
		-DCMAKE_INSTALL_PREFIX=${DEP_INSTALL_DIR}
		-DGLFW_BUILD_EXAMPLES=OFF
		-DGLFW_BUILD_TESTS=OFF
		-DGLFW_BUILD_DOCS=OFF
	)

set(DEP_LIST ${DEP_LIST} dep_glfw)
set(DEP_LIBS ${DEP_LIBS} glfw3)

# glad
ExternalProject_Add(
	dep_glad
	GIT_REPOSITORY "https://github.com/Dav1dde/glad"
	GIT_TAG "v0.1.34"
	GIT_SHALLOW 1
	UPDATE_COMMAND ""
	PATCH_COMMAND ""
	CMAKE_ARGS
		-DCMAKE_INSTALL_PREFIX=${DEP_INSTALL_DIR}
		-DGLAD_INSTALL=ON
	TEST_COMMAND ""
	)
set(DEP_LIST ${DEP_LIST} dep_glad)
set(DEP_LIBS ${DEP_LIBS} glad)

# stb
ExternalProject_Add(
	dep_stb
	GIT_REPOSITORY "https://github.com/nothings/stb"
	GIT_TAG "master"
	GIT_SHALLOW 1
	UPDATE_COMMAND ""
	PATCH_COMMAND ""
	CONFIGURE_COMMAND ""
	BUILD_COMMAND ""
	TEST_COMMAND ""
	INSTALL_COMMAND ${CMAKE_COMMAND} -E copy
		${PROJECT_BINARY_DIR}/dep_stb-prefix/src/dep_stb/stb_image.h
		${DEP_INSTALL_DIR}/include/stb/stb_image.h
	)

set(DEP_LIST ${DEP_LIST} dep_stb)