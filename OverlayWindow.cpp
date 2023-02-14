//
// Created by alex on 2/7/23.
//

#include "OverlayWindow.h"
#include <imgui.h>

static const auto OVERLAY_FLAGS = ImGuiWindowFlags_NoDecoration |
                                  ImGuiWindowFlags_AlwaysAutoResize |
                                  ImGuiWindowFlags_NoSavedSettings |
                                  ImGuiWindowFlags_NoFocusOnAppearing |
                                  ImGuiWindowFlags_NoNav;

OverlayWindow::OverlayWindow()
        : Window("overlay", OVERLAY_FLAGS)
{

}

void OverlayWindow::renderContents()
{
    auto &io = ImGui::GetIO();

    ImGui::Text("Ulmer 3D Game Engine v0.1-dev [Debug] (commit 28398589)");
    ImGui::Text("Dear ImGui %s", ImGui::GetVersion());
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
}
