cmake_minimum_required(VERSION 3.13)

###############################################################################
###############################################################################
#
# This CMake file is provided to make using cppgraphics library as automated
# as possible. When pointed to cppgraphics folder using the variable
# CPPGRAPHICS_CPPGRAPHICS_PATH (defined below), it will build cppgraphics
# dependencies, set the include path, compile cppgraphics source, compile all
# files listed in LIST_OF_FILES (below) and link everything together.
# See `projects/README.md` in cppgraphics repository for more details.


## List of files to compile.
set( LIST_OF_FILES "main.cpp" )

# Set required C++ standard.
set( CPPGRAPHICS_CXX_STANDARD 17 )

# Absolute path to cppgraphics directory. Leave empty for console app.
set( CPPGRAPHICS_CPPGRAPHICS_PATH "${CMAKE_SOURCE_DIR}/../../" CACHE STRING "Path to cppgraphics")

# Should the project support imgui? Enter abs path to imgui or leave empty.
set( CPPGRAPHICS_IMGUI_PATH "" CACHE STRING "Path to imgui")

###############################################################################
###############################################################################


## Set our project name (use directory name)
get_filename_component(PROJECT_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" PROJECT_NAME ${PROJECT_NAME})
project(${PROJECT_NAME} CXX)



# Just for possible debugging:
message("Using CMake ${CMAKE_VERSION}")


set(CMAKE_CXX_STANDARD ${CPPGRAPHICS_CXX_STANDARD})
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)



include(GNUInstallDirs)

if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "No build type selected, default to Release")
  set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Build type (default Release)" FORCE)
endif()


foreach (DIR ${PREFIX_PATH_CHECK})
    if (NOT EXISTS "${DIR}")
        message(FATAL_ERROR "CMAKE_PREFIX_PATH element doesn't exist: ${DIR}")
    endif ()
endforeach ()
message("CMAKE_PREFIX_PATH:${CMAKE_PREFIX_PATH}")





## Print out what compiler was identified and set compiler options
#  Set desired warning level
if (MSVC)
    # CMake<3.15 passed the /Wn argument by itself. Overriding with /W4
    # raises a warning. Remove whatever warning level is set first.
    string(REGEX REPLACE "/W[0-9] " "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /Zc:__cplusplus")
    if ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Od")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")
    endif()
    MESSAGE("MSVC compiler detected")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR "${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
    MESSAGE("GCC/Clang/MinGW detected")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic-errors")
    if ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
    endif()
else()
    MESSAGE(FATAL_ERROR "ERROR: Unknown (and possibly unsupported) compiler. (CMAKE_CXX_COMPILER_ID: '${CMAKE_CXX_COMPILER_ID}')")
endif()


set(CPPGRAPHICS_UNSUPPORTED_GENERATOR FALSE)
if ("${CMAKE_GENERATOR}" STREQUAL "Unix Makefiles")
    if (WIN32 AND NOT MINGW)
        set(CPPGRAPHICS_UNSUPPORTED_GENERATOR TRUE)
    endif()
elseif ("${CMAKE_GENERATOR}" STREQUAL "Ninja")
    if (NOT WIN32 OR NOT "${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
        set(CPPGRAPHICS_UNSUPPORTED_GENERATOR TRUE)
    endif()
endif()
if (CPPGRAPHICS_UNSUPPORTED_GENERATOR)
    MESSAGE(FATAL_ERROR "ERROR: You are attempting to use unsupported combination of build tools. Go to .vscode folder in your project's directory, open settings.json and read comments at the end of the file.")
endif()




# Add cppgraphics srcs to the project.
if (NOT "${CPPGRAPHICS_CPPGRAPHICS_PATH}" STREQUAL "" )
    set( LIST_OF_FILES "${LIST_OF_FILES};${CPPGRAPHICS_CPPGRAPHICS_PATH}/src/cppgraphics.cpp")
    message("The project uses cppgraphics library: ${CPPGRAPHICS_CPPGRAPHICS_PATH}")
else()
    message("The project does NOT use cppgraphics library")
endif()



# Create our target.
set(TARGET_NAME "${PROJECT_NAME}_executable")
add_executable(${TARGET_NAME} ${LIST_OF_FILES})
set_target_properties(${TARGET_NAME} PROPERTIES OUTPUT_NAME ${PROJECT_NAME})





if (NOT "${CPPGRAPHICS_CPPGRAPHICS_PATH}" STREQUAL "" )
    # First add cppgraphics include directory.
    target_include_directories(${TARGET_NAME} PRIVATE "${CPPGRAPHICS_CPPGRAPHICS_PATH}/src/")

    # Find OpenGL
    set(OpenGL_GL_PREFERENCE "GLVND")
    find_package(OpenGL REQUIRED)
    target_include_directories(${TARGET_NAME} PRIVATE "${OPENGL_INCLUDE_DIR}")
    target_link_libraries(${TARGET_NAME} "${OPENGL_LIBRARIES}")
    message("OpenGL found: ${OPENGL_LIBRARIES}")

    # Build deps
    if (WIN32)
        execute_process(COMMAND "${CPPGRAPHICS_CPPGRAPHICS_PATH}/deps/build_deps.bat" ${CMAKE_GENERATOR} ${CMAKE_C_COMPILER} ${CMAKE_CXX_COMPILER} WORKING_DIRECTORY "${CPPGRAPHICS_CPPGRAPHICS_PATH}/deps/")
    else()
        execute_process(COMMAND "sh" "${CPPGRAPHICS_CPPGRAPHICS_PATH}/deps/build_deps.sh" ${CMAKE_GENERATOR} ${CMAKE_C_COMPILER} ${CMAKE_CXX_COMPILER} WORKING_DIRECTORY "${CPPGRAPHICS_CPPGRAPHICS_PATH}/deps/")
    endif()

    # Find SDL2
    find_package(SDL2 2 CONFIG REQUIRED)
    target_link_libraries(${TARGET_NAME} SDL2::SDL2 )


    if (WIN32)
        # Add SDL2 dependencies (needed because it is statically linked)
        target_link_libraries(${TARGET_NAME} winmm setupapi version imm32)
    endif()
endif()



if (NOT "${CPPGRAPHICS_IMGUI_PATH}" STREQUAL "" )
    message("The project uses Dear ImGui library: ${CPPGRAPHICS_IMGUI_PATH}")
    target_sources( ${TARGET_NAME} PUBLIC "${CPPGRAPHICS_IMGUI_PATH}/backends/imgui_impl_sdl.cpp" )
    target_sources( ${TARGET_NAME} PUBLIC "${CPPGRAPHICS_IMGUI_PATH}/backends/imgui_impl_opengl3.cpp" )
    target_sources( ${TARGET_NAME} PUBLIC "${CPPGRAPHICS_IMGUI_PATH}/imgui.cpp" )
    target_sources( ${TARGET_NAME} PUBLIC "${CPPGRAPHICS_IMGUI_PATH}/imgui_demo.cpp" )
    target_sources( ${TARGET_NAME} PUBLIC "${CPPGRAPHICS_IMGUI_PATH}/imgui_draw.cpp" )
    target_sources( ${TARGET_NAME} PUBLIC "${CPPGRAPHICS_IMGUI_PATH}/imgui_tables.cpp" )
    target_sources( ${TARGET_NAME} PUBLIC "${CPPGRAPHICS_IMGUI_PATH}/imgui_widgets.cpp" )
    target_compile_definitions( ${TARGET_NAME} PUBLIC CPPGRAPHICS_SUPPORT_IMGUI)
    target_include_directories( ${TARGET_NAME} PUBLIC "${CPPGRAPHICS_IMGUI_PATH}")
    target_include_directories( ${TARGET_NAME} PUBLIC "${CPPGRAPHICS_IMGUI_PATH}/backends")
endif()




# Tell MSVC we don't want its Release/Debug folders.
if (MSVC)
    set_target_properties( ${TARGET_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build )
    set_target_properties( ${TARGET_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/build )
    set_target_properties( ${TARGET_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/build )
endif()



# Enforce required standard on the target.
target_compile_features(${TARGET_NAME} PUBLIC cxx_std_${CPPGRAPHICS_CXX_STANDARD})



# On Linux, make sure that pthread is found.
if (UNIX AND NOT APPLE)
    set(THREADS_PREFER_PTHREAD_FLAG ON)
    find_package(Threads REQUIRED)
    target_link_libraries( ${TARGET_NAME} Threads::Threads)
endif()
