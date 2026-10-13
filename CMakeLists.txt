
cmake_minimum_required(VERSION 4.3)

project(untitled LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

# GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG 3.4
        GIT_SHALLOW TRUE
)

# GLM
set(GLM_BUILD_TESTS OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
        glm
        GIT_REPOSITORY https://github.com/g-truc/glm.git
        GIT_TAG 1.0.3
        GIT_SHALLOW TRUE
)

# GLAD 2
FetchContent_Declare(
        glad
        GIT_REPOSITORY https://github.com/Dav1dde/glad.git
        GIT_TAG 658f48e72aee3c6582e80b05ac0f8787a64fe6bb
        SOURCE_SUBDIR cmake
)

# Download dependencies
FetchContent_MakeAvailable(glfw glm glad)

# Generate OpenGL 3.3 Core loader
glad_add_library(
        glad_gl_core_33
        STATIC
        REPRODUCIBLE
        LOADER
        API gl:core=3.3
)

# Application
add_executable(untitled main.cpp
        window.h)

target_link_libraries(untitled PRIVATE
        glad_gl_core_33
        glfw
        glm::glm
)
