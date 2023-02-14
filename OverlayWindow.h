#pragma once

#include "Window.h"

class OverlayWindow : public Window
{
public:
    OverlayWindow();

protected:
    void renderContents() override;
};
