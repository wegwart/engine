#pragma once

#include <engine/Window.h>

namespace Engine {
    class DemoWindow : public Window
    {
    public:
        DemoWindow();

        ~DemoWindow() = default;

    protected:
        void renderWindow(bool &isVisible) final;
    };
}