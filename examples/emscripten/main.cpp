#include "cppgraphics.hpp"

int main()
{
    cg::create_window("HELLO WORLD");
    cg::circle(100, 100, 50);
    cg::wait_until_closed();
    return 0;
}
