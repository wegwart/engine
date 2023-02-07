//
// Created by alex on 2/7/23.
//

#include "GuiWindow.h"
#include <imgui.h>

GuiWindow::GuiWindow(const std::string &windowTitle, int flags)
        : m_flags(flags), m_isOpen(true), m_windowTitle(windowTitle)
{

}

void GuiWindow::render()
{
    if (!m_isOpen)
        return;

    ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
    ImGui::Begin(m_windowTitle.c_str(), &m_isOpen, m_flags);
    renderContents();
    ImGui::End();
}
