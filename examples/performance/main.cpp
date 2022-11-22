#include "cppgraphics.hpp"

#include <vector>

// Set number of circles in the background.
const int N = 5000;



struct Circle {
    double x;
    double y;
    double r;
    int color;
};



void draw_circles(const std::vector<Circle>& circles)
{
    cg::set_thickness(10.);
    cg::set_fill_color(cg::Transparent);        
    for (const Circle& circ : circles) {
        cg::set_color(circ.color);
        cg::circle(circ.x, circ.y, circ.r);
    }
}

void draw_legend(bool batches)
{
    cg::set_thickness(0.);
    cg::set_fill_color(cg::Black);
    cg::rectangle(0,0,475,130);
    cg::set_color(cg::White);
    cg::text(std::to_string(N) + " circles (~" + std::to_string(60*N) + " triangles)", 20, 10, 25);
    cg::text(std::string("FPS: ") + std::to_string(cg::get_measured_fps()), 20, 50, 25);
    cg::text(batches ? "using batches" : "not using batches (press a key)", 20, 90, 25);
}

void draw_mouse_circle()
{
    cg::set_fill_color(cg::Black);
    cg::set_thickness(0.);
    cg::circle(cg::get_mouse_x(), cg::get_mouse_y(), 50.);
}

int main()
{
    // Create our window and generate N random circles:
    cg::create_window("Batches test", 800., 450.);
    std::vector<Circle> circles;
    for (size_t i=0; i<N; ++i)
        circles.emplace_back(Circle{double(cg::random_int(800)), double(cg::random_int(450)),
                              double(cg::random_int(100)), 1 + cg::random_int(15)});
    
    ///////////////////////////////////////////////////////////////////////////

    // First try to do the cg::circle calls in each frame. This means the
    // vertices are generated and send to the GPU in each frame:
    while (cg::wait_until_keypressed(0.) == cg::TimeOut) {
        cg::clear();
        draw_circles(circles);
        draw_legend(false);
        draw_mouse_circle();
    }
    // The performance is quite bad, right?
    // If it is not, increase N to see the difference from the latter approach.

    if (! cg::is_window_open())
        return 0;    

    ///////////////////////////////////////////////////////////////////////////

    // Now prepare the circles and send them to the GPU only once:
    cg::begin_batch("CIRCLES");
    draw_circles(circles);
    cg::end_batch();

    // We can even clear our vector now:
    circles.clear();
    circles.shrink_to_fit();
    
    while (cg::refresh()) {
        cg::clear();
        cg::draw_batch("CIRCLES", 0., 0.);
        draw_legend(true);
        draw_mouse_circle();
    }

    // Better, wasn't it?

    ///////////////////////////////////////////////////////////////////////////

    return 0;
}
