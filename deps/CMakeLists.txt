# This CMake project downloads, configures and builds cppgraphics dependencies on Unix and Windows.
# It is a greatly simplified deps-handling CMake from [PrusaSlicer](https://github.com/prusa3d/PrusaSlicer).

cmake_minimum_required(VERSION 3.13)
if(CMAKE_VERSION VERSION_GREATER_EQUAL "3.24.0")
    cmake_policy(SET CMP0135 NEW)
endif()


project(cppgraphics-deps)

include(ExternalProject)

set(DESTDIR "${CMAKE_CURRENT_BINARY_DIR}/destdir" CACHE PATH "Destination directory")
set(DEP_DOWNLOAD_DIR "${CMAKE_CURRENT_BINARY_DIR}/download" CACHE PATH "Path for downloaded source packages.")

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
    message(STATUS "Forcing CMAKE_BUILD_TYPE to Release as it was not specified.")
endif ()


cmake_parse_arguments(P_ARGS "" "INSTALL_DIR;BUILD_COMMAND;INSTALL_COMMAND" "CMAKE_ARGS" ${ARGN})

ExternalProject_Add(
    dep_SDL2
    EXCLUDE_FROM_ALL    ON
    INSTALL_DIR         ${DESTDIR}/usr/local
    DOWNLOAD_DIR        ${DEP_DOWNLOAD_DIR}/${projectname}
    URL https://www.libsdl.org/release/SDL2-2.0.22.zip
    URL_HASH SHA256=9a81ab724e6dcef96c61a4a2ebe7758e5b8bb191794650d276a20d5148fbd50c
    ${_gen}
    CMAKE_ARGS
        -DCMAKE_INSTALL_PREFIX:STRING=${DESTDIR}/usr/local
        -DCMAKE_MODULE_PATH:STRING=${PROJECT_SOURCE_DIR}/../cmake/modules
        -DCMAKE_PREFIX_PATH:STRING=${DESTDIR}/usr/local
        -DCMAKE_DEBUG_POSTFIX:STRING=d
        -DCMAKE_GENERATOR:STRING=${CMAKE_GENERATOR}
        -DCMAKE_C_COMPILER:STRING=${CMAKE_C_COMPILER}
        -DCMAKE_CXX_COMPILER:STRING=${CMAKE_CXX_COMPILER}
        -DCMAKE_TOOLCHAIN_FILE:STRING=${CMAKE_TOOLCHAIN_FILE}
        -DBUILD_SHARED_LIBS:BOOL=OFF
        "${_configs_line}"
        ${DEP_CMAKE_OPTS}
        ${P_ARGS_CMAKE_ARGS}
    ${P_ARGS_UNPARSED_ARGUMENTS}
    BUILD_COMMAND ${CMAKE_COMMAND} --build . --config Release -- ${_build_j}
    INSTALL_COMMAND ${CMAKE_COMMAND} --build . --target install --config Release
)

add_custom_target(deps ALL DEPENDS dep_SDL2)
