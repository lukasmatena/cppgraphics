This guide describes installation of C++ compiler and all tools needed to build cppgraphics project.
Unless you are a complete C++ beginner, you will probably not need it. It is also described many times on the internet, so you can also google for more detailed instructions or videos.


## 1. Install C++ compiler

Compiler is a program that processes your source files and translates them into an executable file for your platform (e.g. an EXE file on Windows). How to install it:

#### Windows
The natural compiler choice on Windows is Microsoft Visual Studio Compiler (MSVC). Go to [Microsoft download website](https://visualstudio.microsoft.com/downloads/), download Visual Studio Installer, run it, select "Desktop Development with C++" and confirm.

#### macOS
Install `clang` compiler: Open terminal window and enter `xcode-select --install`. Then follow the instructions.

#### Linux
GNU Compiler Collection (gcc) should be available through your package manager. On most distros it is enough to install a package called `build-essential`. For example, on Debian-based distros (such as Ubuntu and its derivatives) type `sudo apt install build-essential` into a terminal window and confirm. If you cannot find the package for your distro, see the official [gcc website](https://gcc.gnu.org/) for instructions.





## 2. Install CMake

CMake is a tool used to configure a C++ application build independently on operating system, currently used compiler, etc.

#### Windows
Download the installer of the latest release from [official CMake website](https://cmake.org/download/), run it and proceed with the installation. Make sure that you add CMake to PATH when asked about it.

#### macOS
Download the dmg file of the latest release from [official CMake website](https://cmake.org/download/) and install it. When done, run CMake and select `Tools->How to Install For Command Line Use` and follow the instructions to install symlinks to `/usr/local/bin`. To check that it works correctly, open a new Terminal windows and type `cmake --version` - it should give the installed CMake version, not an error message about the command not being found.

#### Linux
CMake should be available through your package manager. It will probably come as a package named `cmake` (depending on your distribution), it should be enough to install through your package manager. For example, on Debian-based distros (like Ubuntu and derivatives) type `sudo apt install cmake` in the terminal and you are done. To check that it works correctly, open a new Terminal windows and type `cmake --version` - it should give the installed CMake version, not an error message about the command not being found.





## 3. Install Microsoft Visual Studio Code

[Visual Studio Code](https://code.visualstudio.com/) is an IDE (Integrated Development Environment), basically a text editor tailored for programmers and able to invoke all the build tools with little effort. Download the package for your platform from the [official website](https://code.visualstudio.com/#alt-downloads) and install it.

You will probably want to read `projects/README.md` next in order to setup a cppgraphics project.





## Troubleshooting

In case that you run into issues when following the above guide, please, report the problem in the [GitHub issue tracker](https://github.com/lukasmatena/cppgraphics/issues) so it can be fixed. It is likely that some steps will need an update in future.

