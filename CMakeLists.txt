cmake_minimum_required(VERSION 3.22)
project(openGL)

set(CMAKE_CXX_STANDARD 14)
# 检查环境变量
if (NOT DEFINED ENV{GLFW_HOME})
    message(FATAL_ERROR "found no env named GLFW_HOME")
endif()
if (NOT DEFINED ENV{GLAD_HOME})
    message(FATAL_ERROR "found no env named GLAD_HOME")
endif()

# 暂存环境变量
set(GLFW_HOME $ENV{GLFW_HOME})
set(GLAD_HOME $ENV{GLAD_HOME})
set(GLM_HOME $ENV{GLM_HOME})
message( "android ${GLFW_HOME}")

include_directories("${GLFW_HOME}/include")
include_directories("${GLAD_HOME}/include")
include_directories("${GLM_HOME}/glm")

add_library(glfw SHARED IMPORTED)
SET_TARGET_PROPERTIES(glfw PROPERTIES IMPORTED_LOCATION "${GLFW_HOME}/lib/libglfw.3.dylib")

add_executable(openGL main_5_1.cpp "lib/glad.c" shader_s.h stb_image.h Shader.cpp Shader.h)

target_link_libraries(openGL glfw "-framework OpenGL")
