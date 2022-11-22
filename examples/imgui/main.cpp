#include "cppgraphics.hpp"
#include "imgui.h"

int main()
{
    cg::create_window("cppgraphics + imgui demo", 800, 600);
    float r = 100.;
    float thickness = 3.;
    bool circle = false;
    bool dark = true;

    cg::set_fill_color(cg::Red);

    while (cg::refresh()) {
        ImGui::Begin("Controls", nullptr);
        if (ImGui::RadioButton("Circle", circle)
         || ImGui::RadioButton("Square", ! circle))
            circle = ! circle;
        ImGui::Text("");

        cg::clear();
        ImGui::SliderFloat("size", &r, 0.f, 200.f);
        ImGui::SliderFloat("thickness", &thickness, 0.f, 100.f);
        ImGui::Text("");
        if (ImGui::Checkbox("Dark dialog", &dark))
            dark ? ImGui::StyleColorsDark() : ImGui::StyleColorsLight();
        ImGui::Text("");
        if (ImGui::Button("Quit"))
            return 0;
        ImGui::End();

        cg::set_thickness(thickness);
        circle ? cg::circle(400., 300., r) : cg::rectangle(400-r, 300-r, 2*r, 2*r);
    }
    return 0;
}
