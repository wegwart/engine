#include <imgui/imgui.h>
#include <spdlog/spdlog.h>
#include <engine/DemoWindow.h>

using namespace Engine;

DemoWindow::DemoWindow()
        : Window("ImGui Demo Window")
{
    spdlog::debug("demo window constructed");
}

void DemoWindow::renderWindow(bool &isVisible)
{
    ImGui::ShowDemoWindow(&isVisible);
}