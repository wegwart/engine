#pragma once

#include "GuiWindow.h"

class OverlayWindow : public GuiWindow
{
public:
    OverlayWindow();

protected:
    void renderContents() override;
};
