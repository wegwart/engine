//
// Created by alex on 2/14/23.
//

#include "App.h"
#include "Scene.h"
#include "renderer/Camera.h"
#include <glm/gtx/transform.hpp>

using namespace Engine;

Scene::Scene(std::shared_ptr<Renderer::Camera> camera)
        : m_camera(camera)
{

}

const glm::mat4 &Scene::getViewMatrix() const
{
    return m_camera->getViewMatrix();
}
