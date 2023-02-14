//
// Created by alex on 2/14/23.
//

#include "DemoWindow.h"
#include <imgui/imgui.h>
#include <spdlog/spdlog.h>


DemoWindow::DemoWindow()
        : Window("ImGui Demo Window")
{
    spdlog::debug("demo window constructed");
}

void DemoWindow::renderWindow(bool &isVisible)
{
    ImGui::ShowDemoWindow(&isVisible);
}