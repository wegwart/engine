#pragma once

#include <list>
#include <string>
#include <memory>

#include "OverlayWindow.h"

typedef struct GLFWwindow GLFWwindow;

namespace engine {

    class App
    {

    public:
        App();

        ~App() = default;

        static auto getInstance() -> App &;

        /**
         * The exec() method executes the mainloop (i.e. starts the application)
         */
        void exec();

        /**
         * The addWindow() method adds a GUI Window to the list of objects
         * that will get rendered/updated by the mainloop. The shared_ptr
         * to the object will be dropped from the list once the window's
         * closed() function returns true.
         *
         * @param window the "Window" object to render and update
         */
        void addWindow(std::shared_ptr<Window> window);

    private:
        void setupWindow();

        void update();

        void render();

        void renderScene();

        void renderImGui();

        void onResize(int width, int height);

        static void glfwResizeCallback(GLFWwindow *window, int width, int height);

    private:
        static App *s_instance;
        float m_targetFramesPerSecond;

        GLFWwindow *m_window;
        int m_width, m_height;
        bool m_fullscreen;

        std::string m_windowTitle;
        OverlayWindow debugOverlay;
        std::list<std::shared_ptr<Window>> m_windows;
    };

}

