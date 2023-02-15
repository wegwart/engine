#include <engine/Engine.h>
#include <engine/Camera.h>
#include <engine/Scene.h>

using namespace Engine;

Scene::Scene(std::shared_ptr<Renderer::Camera> camera)
        : m_camera(camera)
{

}

const glm::mat4 &Scene::getViewMatrix() const
{
    return m_camera->getViewMatrix();
}
