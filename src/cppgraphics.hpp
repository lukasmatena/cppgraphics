#ifndef CPPGRAPHICS_HPP_INCLUDE_GUARD
#define CPPGRAPHICS_HPP_INCLUDE_GUARD

#include <string>


namespace cg {



///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                               INTRODUCTION                                //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
//
// cppgraphics is a simple C++ library to provide access to graphics output and 
// keyboard / mouse on Windows, Linux and macOS (experimentally Emscripten).
//
// See https://github.com/lukasmatena/cppgraphics
//
// All functions but the advanced ones accept/return bool, int, double
// or std::string. All state information are stored internally.
//
// Functions and constants below are in cg namespace. When calling them,
// namespace qualification must be present, e.g. cg::create_window();
//
// Functions log errors on stderr. Calling a function that needs a window when
// no window is opened terminates the application.
//
// Example Hello world app (OpenGL and SDL2 must be available and
// cppgraphics.cpp must be a part of the project):
//
//    #include "cppgraphics.hpp"
//    int main() {
//        cg::create_window("Hello world");
//        cg::circle(100., 100., 50.);
//        cg::wait_until_closed();
//        return 0;
//     }










///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                                 BASICS                                    //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

// Creates a window with given parameters. Only one window can be opened at a time.
// Width and height set the size of the window and also define the internal coordinate
// system of the window, which does not change even if the window is later resized.
// The contents of the window maintains its aspect ratio in that case.
void create_window(const std::string& title = "cppgraphics window",
                   double width = 800., double height = -1.,
                   bool fullscreen = false);

// Changes window title.
void set_window_title(const std::string& title);

// Changes window size. The coordinate system used for drawing does not change.
void set_window_size(int width, int height);

// Get current window dimensions.
int get_window_width();
int get_window_height();

// Maximizes the window. The coordinate system used for drawing does not change.
void maximize_window();

// Is our window open?
bool is_window_open();

// Does the window currently have focus?
bool has_window_focus();

// Close window, if it exists. Otherwise, the function does nothing.
void close_window();








///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                          KEEPING THE WINDOW ALIVE                         //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

// cppgraphics is single threaded and in order to keep the window responsive,
// it is necessary to let it update often enough. Any of the following
// functions will take care of it (others are described below in the 
// section regarding keyboard and mouse input).

// Wait until the user closes the window.
void wait_until_closed();

// Wait for given amount of time (seconds).
void wait(double sec);

// Process events and refresh window (equivalent to wait(0.)). Returns true
// if the window is alive when the function returns.
bool refresh();







///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                        KEYBOARD AND MOUSE INPUT                           //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

// Get text input from the user. The text shows at given position with given
// height, disappears when confirmed (unless persist is true) and accepts at most
// max_chars characters (negative = no limit). Current font is used (see below).
// Output string is UTF-8 encoded.
std::string read_line(double x, double y, double height,
                      bool persist = false, int max_chars = -1);

// Get current mouse position in window coordinates.
double get_mouse_x();
double get_mouse_y();

// Get current mouse wheel position.
double get_mousewheel_pos();

// Is the key/button currently pressed?
// Accepts a number identifying a key/mouse event. E.g. cg::KeyA,
// cg::MouseLeft, etc. See end of this file for complete list.
bool is_input(int input);

// Following functions return a number identifying key/button that was pressed.
// E.g. cg::KeyA, cg::MouseLeft, etc. See end of this file for complete list.
// They can also return these codes with special meaning:
extern const int TimeOut;      // specified time passed with no input
extern const int WindowClosed; // window was closed while waiting

int wait_until_keypressed(double timeout = -1.); // timeout = -1 : No timeout.
int wait_until_mouse(double timeout = -1.);
int wait_until_input(double timeout = -1); // mouse OR key








///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                       SETTING GRAPHICS ATTRIBUTES                         //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

// cppgraphics holds a list of currently active attributes, which are used
// when a function that draw something is called (see the next section).
// These functions are used to set them.

// Sets all the attributes (except background color) to default values.
void set_defaults();

// Setting colors: accepts a color index from the list below.
void set_color(int color);              // Current color
void set_fill_color(int color);         // Current fill color
void set_background_color(int color);   // Background color (after cg::clear)

// Following functions do the same, but accept RGB(A) values in 0. to 1. range
void set_color(double r, double g, double b, double a = 1.);
void set_fill_color(double r, double g, double b, double a = 1.);
void set_background_color(double r, double g, double b, double a = 1.);

// Set line thickness to be used for lines, triangles, rectangles and circles.
void set_thickness(double thickness);

// Change current font to one loaded from a TTF file. Returns true when
// successful, false when file not found. Calling the function with an empty
// string switches to a built-in font (which is the default). The built-in
// font only supports ASCII, other characters are replaced by a question mark.
bool set_font(const std::string& name);

// Color codes for set_color, set_fill_color, etc.
extern const int Black;
extern const int White;
extern const int Red;
extern const int Green;
extern const int Blue;
extern const int Yellow;
extern const int Magenta;
extern const int Cyan;
extern const int DarkRed;
extern const int DarkGreen;
extern const int DarkBlue;
extern const int Orange;
extern const int Brown;
extern const int Purple;
extern const int Gray;
extern const int DarkGray;
extern const int Transparent;






///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                             DRAWING FUNCTIONS                             //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

// Functions declared in this section use the parameters previously set
// by functions listed in the previous block.

// Clear window and fill it with background color.
void clear();

// Move pencil.
void move_to(double x, double y);

// Draw line from current pencil position to given point.
void line_to(double x, double y);

// Draw line from one point to the other.
void line(double x1, double y1, double x2, double y2);

// Draw a triangle.
void triangle(double x1, double y1, double x2, double y2, double x3, double y3);

// Draw a rectangle ( x,y: top-left corner; a,b: sides)
void rectangle(double x, double y, double a, double b);

// Draw a circle with given center and radius.
void circle(double x, double y, double r);

// Draw image loaded from file 'filename'.
// Bmp, png, tga, jpg, gif, psd, and pnm are supported.
// Functions return true if successful, false when file not found.
// The image is only loaded once, subsequent calls use the cached image.
bool image(const std::string& filename, double x, double y);
bool image(const std::string& filename, double x, double y, double width, double height);

// Draw a part of an image. cut_x, etc. define a rectangle in original image coordinates.
bool image(const std::string& filename, double x, double y, double width, double height,
           int cut_x, int cut_y, int cut_width, int cut_height);


// Following functions draw text (UTF-8 encoded). Current font and color are used.

// Draw text using default font size.
void text(const std::string& str, double x, double y);

// Draw text with a given height.
void text(const std::string& str, double x, double y, double height);

// Draw text to fit a given rectangle (the text may get deformed).
void text(const std::string& str, double x, double y, double width, double height);

// Draw text centered on point (x,y) with given height.
void text_centered(const std::string& str, double x, double y, double height);






///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                         MISCELLANEOUS FUNCTIONS                           //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

// Returns a pseudo-random integer from [0, max] range.
int random_int(int max);

// Returns time (in seconds) since the program started.
double time_since_start();






///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                            ADVANCED FUNCTIONS                             //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

// Colors for blending (see below). vertex_idx is one of 0,1,2,3, accepts the
// same values as the "normal" color-setting functions described above.
void set_blend_color(int vertex_idx, int color);
void set_blend_color(int vertex_idx, double r, double g, double b, double a = 1.);

// Triangle/rectangle with different-coloured vertices (set by set_blend_color).
void triangle_blend(double x1, double y1, double x2, double y2, double x3, double y3);
void rectangle_blend(double x, double y, double a, double b);


// Set desired FPS and steps per second (i.e. how many times per second will
// while (cg::refresh()) { } repeat). Both will drop in reality in case
// it cannot keep up (FPS drops first).
void set_fps(int fps);                  // default = 25
void set_steps_per_second(int steps);   // default = 50

// Get actual FPS (updated once per second).
int get_measured_fps();

// Set color of inactive region of the window (the part that
// shows after resizing changes aspect ratio).
void set_inactive_color(double r, double g, double b, double a = 1.);

// Draw an image created from pixel data. data points to a first pixel, there
// must be source_width*source_height pixels available, each taking 4 bytes (RGBA).
// If called repeatedly with the same pointer, the data are only reloaded when
// reload is true. Otherwise, they are pulled from a cache.
void image(const unsigned char* data, int x, int y, int width, int height,
           int source_width, int source_height, bool reload);

// Any drawing done between begin_batch and end_batch does not appear on screen,
// but is "drawn" into a named buffer. The contents of the buffer may then be
// actually drawn by draw_batch. This (slightly) improves performance when drawing
// the same thing many times, so it is only generated once and not in each frame.
void begin_batch(const std::string& name);
void end_batch();
void draw_batch(const std::string& name, double x = 0., double y = 0.);









///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                               LIST OF KEYS                                //
//                   (see KEYBOARD AND MOUSE INPUT above)                    //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
extern const int KeyUnknown;
extern const int KeyReturn;
extern const int KeyEscape;
extern const int KeyBackspace;
extern const int KeyTab;
extern const int KeySpace;
extern const int KeyComma;
extern const int KeyMinus;
extern const int KeyPeriod;
extern const int KeySlash;
extern const int Key0;
extern const int Key1;
extern const int Key2;
extern const int Key3;
extern const int Key4;
extern const int Key5;
extern const int Key6;
extern const int Key7;
extern const int Key8;
extern const int Key9;
extern const int KeySemicolon;
extern const int KeyEquals;
extern const int KeyLeftbracket;
extern const int KeyBackslash;
extern const int KeyRightbracket;
extern const int KeyA;
extern const int KeyB;
extern const int KeyC;
extern const int KeyD;
extern const int KeyE;
extern const int KeyF;
extern const int KeyG;
extern const int KeyH;
extern const int KeyI;
extern const int KeyJ;
extern const int KeyK;
extern const int KeyL;
extern const int KeyM;
extern const int KeyN;
extern const int KeyO;
extern const int KeyP;
extern const int KeyQ;
extern const int KeyR;
extern const int KeyS;
extern const int KeyT;
extern const int KeyU;
extern const int KeyV;
extern const int KeyW;
extern const int KeyX;
extern const int KeyY;
extern const int KeyZ;
extern const int KeyCapslock;
extern const int KeyF1;
extern const int KeyF2;
extern const int KeyF3;
extern const int KeyF4;
extern const int KeyF5;
extern const int KeyF6;
extern const int KeyF7;
extern const int KeyF8;
extern const int KeyF9;
extern const int KeyF10;
extern const int KeyF11;
extern const int KeyF12;
extern const int KeyPrintscreen;
extern const int KeyScrolllock;
extern const int KeyPause;
extern const int KeyInsert;
extern const int KeyHome;
extern const int KeyPageUp;
extern const int KeyDelete;
extern const int KeyEnd;
extern const int KeyPageDown;
extern const int KeyRight;
extern const int KeyLeft;
extern const int KeyDown;
extern const int KeyUp;
extern const int KeyNumLockClear;
extern const int KeyKP_Divide;
extern const int KeyKP_Multiply;
extern const int KeyKP_Minus;
extern const int KeyKP_Plus;
extern const int KeyKP_Enter;
extern const int KeyKP_1;
extern const int KeyKP_2;
extern const int KeyKP_3;
extern const int KeyKP_4;
extern const int KeyKP_5;
extern const int KeyKP_6;
extern const int KeyKP_7;
extern const int KeyKP_8;
extern const int KeyKP_9;
extern const int KeyKP_0;
extern const int KeyKP_Period;
extern const int KeyLCtrl;
extern const int KeyLShift;
extern const int KeyLAlt;    // alt, option
extern const int KeyLGui;    // windows, command (apple), meta
extern const int KeyRCtrl;
extern const int KeyRShift;
extern const int KeyRAlt;    // alt gr, option
extern const int KeyRGui;    // windows, command (apple), meta



// Mouse event codes
extern const int MouseLeft;
extern const int MouseRight;
extern const int MouseMiddle;
extern const int MouseWheelUp;
extern const int MouseWheelDown;




} // namespace cg

#define CPPGRAPHICS_VERSION_MAJOR 1
#define CPPGRAPHICS_VERSION_MINOR 0
#define CPPGRAPHICS_VERSION_PATCH 1

#endif // CPPGRAPHICS_HPP_INCLUDE_GUARD
