#include "include/engine/Engine.h"
#include "include/engine/Window.h"
#include <imgui.h>
#include <spdlog/spdlog.h>

using namespace Engine;

Window::Window(const std::string &windowTitle, int flags)
        : m_flags(flags)
          , m_isVisible(true)
          , m_windowTitle(windowTitle)
{
    _internal::registerWindow(this);
}

Window::~Window()
{
    //_internal::unregisterWindow(this);
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