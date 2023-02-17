#include <glm/gtx/transform.hpp>
#include <engine/Camera.h>

using namespace Engine::Renderer;

Camera::Camera(glm::vec3 cameraPosition, glm::vec3 lookAtPoint, glm::vec3 upVector)
        : m_cameraPosition(cameraPosition)
          , m_lookAtPoint(lookAtPoint)
          , m_upVector(upVector)
{
    updateViewMatrix();
}

void Camera::setPosition(glm::vec3 cameraPosition)
{
    m_cameraPosition = cameraPosition;
    updateViewMatrix();
}

void Camera::setLookAtPoint(glm::vec3 lookAtPoint)
{
    m_lookAtPoint = lookAtPoint;
    updateViewMatrix();
}

void Camera::updateViewMatrix()
{
    // glm::lookAt() builds a camera view matrix for us that can be used as a part of the MVP matrix
    // in the vertex shader to render the scene according to the camera position and orientation.
    m_viewMatrix = glm::lookAt(m_cameraPosition, m_lookAtPoint, m_upVector);
}
