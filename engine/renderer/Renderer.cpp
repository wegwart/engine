#include <GL/glew.h>
#include <engine/Renderer.h>

void Engine::Renderer::clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Engine::Renderer::setClearColor(glm::vec3 color)
{
    glClearColor(color.x, color.y, color.z, 1.0);
}

