**!!! FIRST READ [docs/How_to_build.md](../../docs/How_to_build.md) !!!**

If you have read it and are sure that you want to build this example project
manually, copy `src/cppgraphics.cpp` and `src/cppgraphics.hpp` into this
folder. Then just build the project in the usual CMake way:

    mkdir build
    cd build
    cmake ..
    cmake --build . --config Release

In order for that to work, you have to make sure that CMake finds SDL2. How you
do it is up to you.



One of the possibilities is to download and build SDL2 using the script in
cppgraphics `deps/` folder and then point CMake to it.

In that case, you would run:

    cd cppgraphics/deps
    build_deps.bat (or ./build_deps.sh on Linux/macOS)

Then you can build this project as described above, passing an extra argument
`-DCMAKE_PREFIX_PATH=(absolute path to cppgraphics)/deps/build/destdir/usr/local"`
to CMake. You can move the compiled SDL2 wherever else you like.
