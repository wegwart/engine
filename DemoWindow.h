//
// Created by alex on 2/14/23.
//

#pragma once

#include "Window.h"

class DemoWindow : public Window
{
public:
    DemoWindow();

    ~DemoWindow() = default;

protected:
    void renderWindow(bool &isVisible) final;

};