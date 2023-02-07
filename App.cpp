#include <cassert>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <spdlog/spdlog.h>
#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>

#include "App.h"
#include "OverlayWindow.h"

static const char *GLSL_VERSION = "#version 130";
#define OPENGL_VERSION_MAJOR 3
#define OPENGL_VERSION_MINOR 0

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

static bool showDemo = true;

void App::exec()
{
    setupWindow();

    OverlayWindow debugOverlay;

    while (!glfwWindowShouldClose(m_window))
    {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        debugOverlay.render();

        ImGui::Render();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

//        if (s_scene)
//            s_scene->render();

        glfwSwapBuffers(m_window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(m_window);
    glfwTerminate();
}

void App::setupWindow()
{
    if (!glfwInit())
    {
        spdlog::critical("glfwInit() failed");
        assert(false);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_VERSION_MAJOR);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_VERSION_MINOR);

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


    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(m_window, true);
    ImGui_ImplOpenGL3_Init(GLSL_VERSION);

    spdlog::debug("ImGui setup complete");

    spdlog::debug("initializing GLEW (OpenGL)");
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

