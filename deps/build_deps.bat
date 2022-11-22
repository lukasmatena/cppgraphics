@echo off

REM The script expects three string arguments: generator, c compiler, c++ compiler


echo =========================


REM The script assumes to be run in the same dir as where it is:
if NOT EXIST build_deps.bat (
    echo ERROR: build_deps.bat run with a wrong workdir.
    exit /B 1
)

set CG_CMAKE_GENERATOR="%1%"
set CG_CMAKE_C_COMPILER="%2%"
set CG_CMAKE_CXX_COMPILER="%3%"
REM Remove quotes:
set CG_CMAKE_GENERATOR=%CG_CMAKE_GENERATOR:"=%
set CG_CMAKE_C_COMPILER=%CG_CMAKE_C_COMPILER:"=%
set CG_CMAKE_CXX_COMPILER=%CG_CMAKE_CXX_COMPILER:"=%
set CG_COMPILERS="%CG_CMAKE_GENERATOR%%CG_CMAKE_C_COMPILER%%CG_CMAKE_CXX_COMPILER%"
set CG_COMPILERS=%CG_COMPILERS:"=%

REM Read old generator and compare to current.
set /p CG_OLD_COMPILERS=<".\build\cg_compilers.txt"
if NOT "%CG_OLD_COMPILERS%" == "%CG_COMPILERS%" (
    echo Compiler has changed, removing build dir...
    rmdir /S /Q .\build
)

if "%CG_CMAKE_GENERATOR%"=="" (
    cmake . -B".\build"
) else (
    cmake . -B".\build" -G"%CG_CMAKE_GENERATOR%" -DCMAKE_C_COMPILER="%CG_CMAKE_C_COMPILER%" -DCMAKE_CXX_COMPILER="%CG_CMAKE_CXX_COMPILER%"
)

if %errorlevel% neq 0 (
    echo ERROR: CMake configuration of deps failed, see errors above.
    echo =========================
    exit /B 1
) else (
    echo CMake configuration of deps ok.
)


cmake --build ".\build" --config Release

if %errorlevel% neq 0 (
    echo ERROR: Build of deps failed, see errors above.
    echo =========================
    exit /B 1
) else (
    echo Build of deps finished. Caching used compiler...
)


REM The build was successful. Remember used generator.
echo %CG_COMPILERS%>".\build\cg_compilers.txt"
echo Dependencies successfully built!


echo =========================
