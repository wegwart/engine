//
// Created by alex on 2/14/23.
//

#include "Renderer.h"
#include <GL/glew.h>
#include <spdlog/spdlog.h>

static void glErrorCallback(
        GLenum source, GLenum type, GLuint id,
        GLenum severity, GLsizei length,
        const GLchar *message, const void *userParam
)
{
    (void) source;
    (void) length;
    (void) type;
    (void) severity;
    (void) userParam;

    spdlog::error("OpenGL error: {} (id={})", message, id);
}

bool Engine::Renderer::init()
{
    auto err = glewInit();
    if (err != GLEW_OK)
    {
        spdlog::critical("glewInit() failed (GLenum = {})", err);
        return false;
    }

    int versionMajor, versionMinor;
    glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
    glGetIntegerv(GL_MINOR_VERSION, &versionMinor);
    spdlog::info("OpenGL version is {}.{}", versionMajor, versionMinor);

    glDebugMessageCallback(glErrorCallback, nullptr);
    return true;
}