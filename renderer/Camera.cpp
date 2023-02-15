//
// Created by alex on 2/15/23.
//

#include "Camera.h"
#include <glm/gtx/transform.hpp>

using namespace Engine::Renderer;

Camera::Camera(glm::vec3 cameraPosition, glm::vec3 lookAtPoint, glm::vec3 upVector)
        : m_cameraPosition(cameraPosition),
          m_lookAtPoint(lookAtPoint), m_upVector(upVector)
{
    updateViewMatrix();
}

void Camera::setCameraPosition(glm::vec3 cameraPosition)
{
    m_cameraPosition = cameraPosition;
    updateViewMatrix();
}

void Camera::updateViewMatrix()
{
    m_viewMatrix = glm::lookAt(m_cameraPosition, m_lookAtPoint, m_upVector);
}