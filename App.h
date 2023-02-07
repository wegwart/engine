#pragma once

#include <string>

#include <GLFW/glfw3.h>

namespace engine {

    class App
    {

    public:
        App();

        ~App() = default;

        void exec();

        static auto getInstance() -> App &;

        void setWindowTitle(const std::string &title)
        {
            m_windowTitle = title;
        }

        void setFullscreen()
        {
            m_fullscreen = true;
        }

    protected:
        virtual void onInit()
        {}

        virtual void onExit()
        {}

    private:
        void setupWindow();

        static void glfwResizeCallback(GLFWwindow *window, int width, int height);

        void resized(int width, int height);

        static App *s_instance;
        GLFWwindow *m_window;
        int m_width, m_height;
        bool m_fullscreen;
        std::string m_windowTitle;
    };

}

