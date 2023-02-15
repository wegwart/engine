#pragma once

#include <string>

namespace Engine {
    class Window
    {
    public:
        Window(const std::string &windowTitle, int flags = 0);

        virtual ~Window();

        void render();

        inline bool closed() const
        {
            return !m_isVisible;
        }

    protected:
        virtual void renderWindow(bool &isVisible);

        virtual void renderContents()
        {}

    private:
        int m_flags;
        bool m_isVisible;
        std::string m_windowTitle;
    };
}