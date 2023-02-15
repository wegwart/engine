//
// Created by alex on 2/7/23.
//

#include "Window.h"
#include <imgui.h>
#include <spdlog/spdlog.h>

Window::Window(const std::string &windowTitle, int flags)
        : m_flags(flags), m_isVisible(true), m_windowTitle(windowTitle)
{
    spdlog::debug("Window created (\"{}\")", m_windowTitle);
}

Window::~Window()
{
    spdlog::debug("Window deleted (\"{}\")", m_windowTitle);
}


void Window::render()
{
    renderWindow(m_isVisible);
}

void Window::renderWindow(bool &isVisible)
{
    if (isVisible)
    {
        ImGui::Begin(m_windowTitle.c_str(), &isVisible, m_flags);
        renderContents();
        ImGui::End();
    }
}