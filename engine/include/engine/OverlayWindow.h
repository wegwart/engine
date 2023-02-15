#pragma once

#include <engine/Window.h>

namespace Engine {
    class OverlayWindow : public Window
    {
    public:
        OverlayWindow();

    protected:
        void renderContents() override;
    };
}