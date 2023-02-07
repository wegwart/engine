#pragma once

#include <string>

class GuiWindow
{
public:
    GuiWindow(const std::string &windowTitle, int flags = 0);

    virtual ~GuiWindow() = default;

    void render();

protected:
    virtual void onClose()
    {}

    virtual void renderContents() = 0;

private:
    int m_flags;
    bool m_isOpen;
    std::string m_windowTitle;
};

