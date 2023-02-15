#include <cassert>
#include <chrono>
#include <thread>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>
#include <glm/gtx/transform.hpp>

#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>

#include "App.h"
#include "Scene.h"
#include "DemoWindow.h"
#include "OverlayWindow.h"
#include "renderer/Renderer.h"

static const char *GLSL_VERSION = "#version 130";
#define OPENGL_VERSION_MAJOR 3
#define OPENGL_VERSION_MINOR 0

using namespace Engine;

App *App::s_instance = nullptr;

App::App()
        : m_targetFramesPerSecond(30.0f), m_width(1024), m_height(768), m_fullscreen(false),
          m_windowTitle("Ulmer 3D Game Engine")
{
    assert(s_instance == nullptr);
    s_instance = this;

    setupWindow();
}

auto App::getInstance() -> App &
{
    assert(s_instance != nullptr);
    return *s_instance;
}


void App::setupWindow()
{
    // TODO: I don't like this large method. Split up in smaller parts, move to other files...?

    if (!glfwInit())
    {
        spdlog::critical("glfwInit() failed");
        assert(false);
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    //glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_VERSION_MAJOR);
    //glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_VERSION_MINOR);

    spdlog::debug("fullscreen: {}", m_fullscreen ? "yes" : "no");
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
    updateProjectionMatrix();
    glfwMakeContextCurrent(m_window);
    spdlog::debug("created window with size ({}, {})", m_width, m_height);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(m_window, true);
    ImGui_ImplOpenGL3_Init(GLSL_VERSION);

    if (!Renderer::init())
    {
        glfwTerminate();
        assert(false);
    }

    spdlog::debug("enable anti-aliasing (4-sample multisampling)");
    glEnable(GL_MULTISAMPLE);

    spdlog::debug("enabling GL_DEPTH_TEST, GL_MULTISAMPLE");
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.00, 0.8, 1.0, 1.0); // Sky blue
}

void App::exec()
{
    auto lastTimestamp = std::chrono::system_clock::now();
    while (!glfwWindowShouldClose(m_window))
    {
        update();
        render();

        const auto targetFrameDuration = std::chrono::nanoseconds((long) (1000000000 / m_targetFramesPerSecond));
        const auto nextFrameTime = lastTimestamp + targetFrameDuration;
        std::this_thread::sleep_until(nextFrameTime);
        lastTimestamp += targetFrameDuration;
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(m_window);
    glfwTerminate();
}

void App::update()
{
    glfwPollEvents();

    if (m_scene)
    {
        m_scene->update();
    }
}

void App::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    renderScene();
    renderImGui();

    glfwSwapBuffers(m_window);
}

void App::renderScene()
{
    if (m_scene)
    {
        m_scene->render(m_projectionMatrix);
    }
}

void App::renderImGui()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    auto window = m_windows.begin();
    while (window != m_windows.end())
    {
        assert(*window != nullptr);
        (*window)->render();

        if ((*window)->closed())
        {
            window = m_windows.erase(window);
        } else
        {
            window++;
        }
    }

    // === HACK BEGIN
    debugOverlay.render();
    ImGui::Begin("FPS Selector");
    ImGui::SliderFloat("FPS", &m_targetFramesPerSecond, 5, 60);
    if (ImGui::Button("Show ImGui Demo Window"))
    {
        addWindow(std::make_shared<DemoWindow>());
    }
    ImGui::End();
    // === HACK END

    ImGui::Render();

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void App::addWindow(std::shared_ptr<Window> window)
{
    m_windows.push_back(window);
}

void App::onResize(int width, int height)
{
    m_width = width;
    m_height = height;

    updateProjectionMatrix();
}

void App::updateProjectionMatrix()
{
    m_projectionMatrix = glm::perspective(
            glm::radians(45.0f), (float) m_width / (float) m_height, 1.0f, 100.0f
    );
}

void App::glfwResizeCallback(GLFWwindow *window, int width, int height)
{
    (void) window;
    App::getInstance().onResize(width, height);
    glViewport(0, 0, width, height);
}

void App::setScene(std::shared_ptr<Scene> scene)
{
    m_scene = scene;
}