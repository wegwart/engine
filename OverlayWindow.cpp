//
// Created by alex on 2/7/23.
//

#include "OverlayWindow.h"
#include <config.h>
#include <imgui.h>

using namespace Engine;

static const auto OVERLAY_FLAGS = ImGuiWindowFlags_NoDecoration |
                                  ImGuiWindowFlags_AlwaysAutoResize |
                                  ImGuiWindowFlags_NoSavedSettings |
                                  ImGuiWindowFlags_NoFocusOnAppearing |
                                  ImGuiWindowFlags_NoNav |
                                  ImGuiWindowFlags_NoBackground;

OverlayWindow::OverlayWindow()
        : Window("overlay", OVERLAY_FLAGS)
{

}

void OverlayWindow::renderContents()
{
    auto &io = ImGui::GetIO();

    ImGui::Text("%s %s [%s] (commit %s); built on %s",
                Engine::BuildInfo::FULL_NAME,
                Engine::BuildInfo::VERSION,
                Engine::BuildInfo::BUILD_TYPE,
                Engine::BuildInfo::BUILD_COMMIT,
                Engine::BuildInfo::BUILD_DATE
    );
    ImGui::Text("Copyright (C) %s", Engine::BuildInfo::AUTHORS);
    ImGui::Text("Dear ImGui %s", ImGui::GetVersion());
    ImGui::Text("Average FPS: %.1f (%.3f ms/frame)", io.Framerate, 1000.0f / io.Framerate);
}
