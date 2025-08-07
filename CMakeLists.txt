cmake_minimum_required(VERSION 3.14)
project(Mini3DViewer LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Inclure glad
include_directories(Lib/glad/include)

# Inclure GLFW (installé via brew)
find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
include_directories(${GLFW_INCLUDE_DIRS})
link_directories(${GLFW_LIBRARY_DIRS})

# Pour compiler tout les fichiers qui suivent les règles.
# # Sources
# file(GLOB_RECURSE SOURCES
#     src/*.cpp
#     Lib/glad/src/glad.c
# )

# Précision de quel fichier .cpp doit être compilé.
set(SOURCES_CPP
    src/main.cpp
    src/Mesh.cpp
    src/Renderer.cpp
)

# Précision de quel fichier .c doit être compilé.
set(SOURCES_C
    Lib/glad/src/gl.c
)

add_executable(Mini3DViewer ${SOURCES_CPP} ${SOURCES_C})

# Link GLFW + OpenGL
target_link_libraries(Mini3DViewer
    ${GLFW_LIBRARIES}
    "-framework OpenGL"
)
