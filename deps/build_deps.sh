#!/bin/sh

# The script expects three string arguments: generator, c compiler, c++ compiler


printf "=========================\n"


# The script assumes to be run in the same dir as where it is:
if [ ! -f "build_deps.sh" ]; then
    printf "ERROR: build_deps.bat run with a wrong workdir.\n"
    return 1
fi



CG_CMAKE_GENERATOR=${1}
CG_CMAKE_C_COMPILER=${2}
CG_CMAKE_CXX_COMPILER=${3}
CG_OLD_CMAKE_COMPILERS=`cat "./build/cg_compilers.txt"`


if [ ! "${CG_CMAKE_GENERATOR}${2}${3}" = "${CG_OLD_CMAKE_COMPILERS}" ]; then
    printf "Compiler has changed, removing build dir...\n"
    rm -rf ./build/
fi

if [ -z "${CG_CMAKE_CXX_COMPILER}" ]; then
    cmake . -B".\build" #TODO: Detect and report errors.
else
    cmake . -B".\build" -G"${CG_CMAKE_GENERATOR}" -DCMAKE_C_COMPILER="${CG_CMAKE_C_COMPILER}" -DCMAKE_CXX_COMPILER="${CG_CMAKE_CXX_COMPILER}"
fi

if [ $? -eq 0 ]; then
  echo "CMake configuration of deps ok."
else
  echo "ERROR: CMake configuration of deps failed, see errors above."
  echo "========================="
  return 1
fi




cmake --build ".\build" --config Release

if [ $? -eq 0 ]; then
    echo "Build of deps finished. Caching used compiler..."
else
    echo "ERROR: Build of deps failed, see errors above."
    echo "========================="
    return 1
fi


# The build was successful. Remember used generator.
echo "${CG_CMAKE_GENERATOR}${2}${3}">"./build/cg_compilers.txt"
echo "Dependencies successfully built!"


echo "========================="
