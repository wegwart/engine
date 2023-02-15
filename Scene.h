//
// Created by alex on 2/14/23.
//

#pragma once

#include <memory>
#include <glm/glm.hpp>

namespace Engine {
    namespace Renderer {
        class Camera;
    }

    class Scene
    {
    public:
        Scene(std::shared_ptr<Renderer::Camera> camera);

        virtual ~Scene() = default;

        virtual void update()
        {}

        virtual void render(const glm::mat4 &projectionMatrix) = 0;

    protected:
        const glm::mat4 &getViewMatrix() const;

        std::shared_ptr<Renderer::Camera> getCamera() const
        {
            return m_camera;
        }

    private:
        std::shared_ptr<Renderer::Camera> m_camera;
    };
}