#pragma once

#include <memory>

namespace EngineApp {
    void onInit();
}

namespace Engine {

    class Scene;

    class Window;

    /**
     * The setScene() method sets the currently active scene.
     *
     * @param scene A shared_ptr to the Scene object
     */
    void setScene(std::shared_ptr<Scene> scene);

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

