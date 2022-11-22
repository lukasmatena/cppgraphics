#include "cppgraphics.hpp"

int main()
{
    cg::create_window("HELLO WORLD");
    cg::set_background_color(0.9, 0.9, 0.9);
    cg::clear();

    cg::set_color(cg::Black);
    cg::set_thickness(2.);
    cg::set_fill_color(cg::Yellow);
    cg::circle(400, 400, 300);

    cg::set_color(cg::Black);
    cg::set_fill_color(cg::Yellow);
    cg::set_thickness(15.);
    cg::circle(400, 400, 200);
    cg::set_color(cg::Yellow);
    cg::rectangle(180, 200, 440, 250);

    cg::set_color(cg::Black);
    cg::set_fill_color(cg::Black);
    cg::circle(320, 300, 30);
    cg::circle(480, 300, 30);

    cg::wait_until_closed();
    return 0;
}
