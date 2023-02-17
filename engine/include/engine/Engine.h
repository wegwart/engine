#pragma once

#include <memory>

namespace EngineApp {

    /**
     * Framework entry point. Implement this function in your code and
     * use it as your entry point to initialize stuff and set the scene.
     */
    void onInit();
}

namespace Engine {

    class Scene;

    class Window;

    /**
     * The setScene() method sets the scene that is currently rendering on the
     * main viewport of the application.
     *
     * @param scene A shared_ptr to the Scene object
     */
    void setScene(std::shared_ptr<Scene> scene);

    /**
     * Get/set the current framerate limit. Note that this value only
     * represents the upper limit. To get the actual framerate, use
     * ImGui::GetIO().Framerate,  for example.
     *
     * @return A reference to the current framerate limit.
     */
    float &framerateLimit();

    namespace _internal {
        /**
         * The registerWindow() method adds a GUI Window to the list of objects
         * that will get rendered/updated by the mainloop.
         *
         * @param window the "Window" object to render and update
         */
        void registerWindow(Window *window);

        /**
         * The unregisterWindow() method removes a GUI Window from the list
         * of objects that will get rendered/updated by the mainloop. The 'shared_ptr'
         * reference to the object will be dropped.
         *
         * @param window the "Window" object to no longer render and update
         */
        void unregisterWindow(Window *window);
    }
}
