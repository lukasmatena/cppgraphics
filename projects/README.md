# Summary

The `projects/` folder contains template projects for [Microsoft Visual Code IDE](https://code.visualstudio.com) with cppgraphics integrated. You can just make a copy of the template project for your platform and then open the folder in Visual Studio Code. It will automatically build SDL2 in the `deps/` folder and then build your project and link to it. This way you will get the application running with no effort. More detailed info follows.

If you don't use Visual Studio Code, it is not difficult to invoke the same build process from the command line. This is described at the bottom of this document.

The whole process is also shown in a tutorial video on YouTube: https://youtu.be/_Rz0ZMLWmC0.





# Step-by-step guide

## 0. Prerequisities

Before you continue, make sure that you have installed

- C++ compiler
- CMake (added to PATH)
- Visual Studio Code

There is a beginner-grade guide located in `docs/Cpp_setup.md` in case you need help with these.





## 1. Run Visual Studio Code and install required extension

Run Visual Studio Code. After optionally selecting your preffered user interface theme, select 'View->Extensions' from the main menu. Then find and install `C/C++ Extension Pack` (by Microsoft).

When the installation finishes, close Visual Studio Code again.





## 2. Create your first project

Unless you have already done so, download cppgraphics repository, ideally to a location with no spaces and non-ASCII characters in the path. Now go into `projects/` and make a copy of the `000_template_xxx` folder for your platform (you can remove the other one). Rename the copy to how you want to name your project. Stick to English letters, digits and underscores, no spaces and no fancy unicode letters. The numbers prepending the project names are not mandatory, although they may be useful for avoiding clutter.





## 3. Build your project in VS Code

Then run Visual Studio Code, select `File->Open Folder` from the menu, navigate into the newly created folder and click Open. You will be prompted to select a compiler kit in a dropdown at the top of the window - select the compiler that is installed on your system and wait until all gets done. Then select Explorer from the left vertical menu and you should see `main.cpp` as one of the files in the folder. Open it and you'll see the source code. Click 'Build' button in the bottom toolbar. Then you can build and run your application by clicking the "Play" button in the bottom toolbar (or pressing Shift+F5). A small black window should appear.





# Notes

All projects created this way in the `projects/` subdirectory only need to `#include "cppgraphics.hpp"` to make cppgraphics library available and working. You can even create several more directories for you projects, if you want to organize your work. As long as they are located in the `cppgraphics/` folder, they will work as described above. For example, the final directory structure could be:


```
├── cppgraphics/
│   ├── deps/
│   ├── docs/
│   ├── examples/
│   ├── projects/
│   │   ├── 000_template/
│   │   │   ├── .vscode
│   │   │   ├── CMakeLists.txt
│   │   │   └── main.cpp
│   │   │
│   │   ├── 001_my_first_app/
│   │   │   ├── .vscode
│   │   │   ├── CMakeLists.txt
│   │   │   └── main.cpp
│   │   ├── ...
│   │   └── ...
│   │
│   ├── more_projects/
│   │   ├── another_app/
│   │   │   ├── .vscode
│   │   │   ├── CMakeLists.txt
│   │   │   └── main.cpp
│   │   ├── ...
│   │   └── ...
│   ├── src
│   ├── CHANGELOG.md
│   ├── LICENCE.md
│   └── README.md
```

If you want to keep your projects out of the cppgraphics directory, it is possible, but then you have to set path to cppgraphics directory at the top of each project's CMakeLists.txt.





## Troubleshooting

In case that you run into issues, try the following:

- In Visual Studio Code, press Ctrl+Shift+P to open Command Palette, find 'CMake: Delete Cache and Reconfigure' and try to build again.
- Close Visual Studio Code, delete `build/` subfolder in your project folder and try again.
- Close Visual Studio Code, delete `deps/build/` subfolder in cppgraphics folder and try again.
- Try all of the above at the same time and only then try to build again.

If none of the above helps, please, report the problem in the [GitHub issue tracker](https://github.com/lukasmatena/cppgraphics/issues) so it can be fixed. The above process was tested on various versions of Windows (MSVC, MinGW), Linux (GCC) and macOS (Clang), but there may still be a problem in scenarios I did not test.





# Alternative build without Visual Studio Code

If you do not use Visual Studio Code, you can still easily build the template projects from the command line. In that case just skip step (1) in the above guilde and instead of step (3) just `cd` into the folder that you created in step (2) and do this:

    mkdir build
    cd build
    cmake .. -DCMAKE_PREFIX_PATH="%cd%/../../../deps/build/destdir/usr/local"
    cmake --build . --config Release

These commands are for Windows. On Linux/macOS, use `$(pwd)` instead of `%cd%`.

This will build the project for you, just like VS Code would.
