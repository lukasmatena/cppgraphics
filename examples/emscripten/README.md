## An example of compiling cppgraphics project with Emscripten.



### Notes on file embedding

The WASM application will not have access to your filesystem. In order to open
data files, images, etc., your must embed them during build. Following guide
assumes that you would move such files into `app_resources` directory.
To open them, your application must use relative path including the subfolder
name. For example, if there is an `image.png` located in the folder,
the application would draw it using `cg::image("app_resources/image.png", 0,0)`.



### How to build

After you have initialized Emscripten environment (https://emscripten.org/docs/getting_started/downloads.html),
cd into this folder and

    mkdir build
    cd build
    mkdir app_resources
    ( copy all files accessed by the application (images, data files, etc.) into app_resources )
    emcc -O3 -s ASYNCIFY ../main.cpp ../../../src/cppgraphics.cpp -s USE_SDL=2 -I../../../src/ -o "output.html" -s USE_WEBGL2=1 --preload-file app_resources



### How to test

The compiler should create several files, including `output.html`. In order to
run your application, you must run a local HTTP server, not just open the html
file. Probably the simplest way to do it is to run (in the `/build` folder)

    python3 -m http.server

And then open `localhost:8000/output.html` in your browser.



### Remarks

Tested on Win 11 + emsdk 3.1.8. Report any issues.
