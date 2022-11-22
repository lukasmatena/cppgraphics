## Building a project inside cppgraphics repository

cppgraphics comes with a template project and CMake scripts that take care
of everything automatically (found in `projects/` folder). It is especially
simple to use with Visual Studio Code. 

If you don't use Visual Studio Code, you can still invoke the same process
from the command line. This is described at the bottom of the guide
mentioned above.

The process for both cases is described in a guide in `projects/README.md`.






## Building a project without relying on cppgraphics helper scripts

If you want to take care of the dependencies yourself, then it is best to look
into the CMake scripts that the template project uses. In general, you need to:

- add `src/cppgraphics.cpp` into your project
- ensure access to `src/cppgraphics.hpp`
- ensure access to SDL2 and OpenGL includes
- link against SDL2 and OpenGL

You can have a look into `examples/manual_build`, where you can find a minimal
CMakeLists.txt which does not rely on any scripts outside its own directory and
a dedicated README.md






### Building with Dear ImGui support

See `examples/imgui/README.md`.
