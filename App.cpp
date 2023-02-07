#include <cassert>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <spdlog/spdlog.h>

#include "App.h"

using namespace engine;

App *App::s_instance = nullptr;

App::App()
        : m_width(1024), m_height(768), m_windowTitle("Ulmer 3D Game Engine")
{
    assert(s_instance == nullptr);
    s_instance = this;
}

auto App::getInstance() -> App &
{
    assert(s_instance != nullptr);
    return *s_instance;
}

void App::exec()
{
    setupWindow();

    while (!glfwWindowShouldClose(m_window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//        if (s_scene)
//            s_scene->render();

        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }

    glfwTerminate();
}

void App::setupWindow()
{
    if (!glfwInit())
    {
        spdlog::critical("glfwInit() failed");
        assert(false);
    }

    auto monitor = m_fullscreen ? glfwGetPrimaryMonitor() : nullptr;
    if (monitor != nullptr)
    {
        auto videoMode = glfwGetVideoMode(monitor);
        m_width = videoMode->width;
        m_height = videoMode->height;
    }

    m_window = glfwCreateWindow(m_width, m_height, m_windowTitle.c_str(), monitor, nullptr);
    if (!m_window)
    {
        spdlog::critical("glfwCreateWindow() failed");

        glfwTerminate();
        assert(false);
    }

    glfwGetWindowSize(m_window, &m_width, &m_height);
    glfwSetWindowSizeCallback(m_window, &App::glfwResizeCallback);
    glfwMakeContextCurrent(m_window);
    spdlog::debug("created window with size ({}, {})", m_width, m_height);

    auto err = glewInit();
    if (err != GLEW_OK)
    {
        spdlog::critical("glewInit() failed (GLenum = {})", err);

        glfwTerminate();
        assert(false);
    }

    spdlog::debug("enabling GL_DEPTH_TEST");
    glEnable(GL_DEPTH_TEST);
}

void App::glfwResizeCallback(GLFWwindow *window, int width, int height)
{
    (void) window;
    App::getInstance().resized(width, height);
    glViewport(0, 0, width, height);
}

void App::resized(int width, int height)
{
    m_width = width;
    m_height = height;

    // s_scene->resized(s_width, s_height);
}

