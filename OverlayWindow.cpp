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
        : GuiWindow("overlay", OVERLAY_FLAGS)
{

}

void OverlayWindow::renderContents()
{
    ImGui::Text("Ulmer 3D Game Engine v0.1-dev [Debug] (commit 28398589)");
}
