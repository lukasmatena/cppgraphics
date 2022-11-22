cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)

project(hello_world CXX)
add_executable(hello_world_executable "main.cpp" "cppgraphics.cpp")

set(OpenGL_GL_PREFERENCE "GLVND")

find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)

target_include_directories(hello_world_executable PRIVATE ${SDL2_INCLUDE_DIRS})
target_include_directories(hello_world_executable PRIVATE ${OPENGL_INCLUDE_DIR})

target_link_libraries(hello_world_executable ${SDL2_LIBRARIES} OpenGL::GL ${CMAKE_DL_LIBS})

set_property(TARGET hello_world_executable PROPERTY CXX_STANDARD 11)
set_property(TARGET hello_world_executable PROPERTY CXX_STANDARD_REQUIRED ON)

if (UNIX AND NOT APPLE)
    set(THREADS_PREFER_PTHREAD_FLAG ON)
    find_package(Threads REQUIRED)
    target_link_libraries( hello_world_executable Threads::Threads)
endif()
if (WIN32)
    # Add SDL2 dependencies (needed because it is statically linked)
    target_link_libraries(world_executable winmm setupapi version imm32)
endif()
