//
// Created by alex on 2/15/23.
//

#include "Shader.h"
#include "ShaderProgram.h"
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>
#include <spdlog/spdlog.h>

using namespace Engine::Renderer;

ShaderProgram::ShaderProgram()
        : m_id(glCreateProgram())
{
}

ShaderProgram::~ShaderProgram()
{
    glDeleteProgram(m_id);
}

bool ShaderProgram::link()
{
    glLinkProgram(m_id);

    int success;
    char messageBuffer[512];
    glGetProgramiv(m_id, GL_LINK_STATUS, &success);

    if (!success)
    {
        glGetProgramInfoLog(m_id, sizeof(messageBuffer), nullptr, messageBuffer);
        spdlog::error("OpenGL: error linking shader: {}", messageBuffer);
        return false;
    }

    return true;
}

void ShaderProgram::bind()
{
    glUseProgram(m_id);
}

void ShaderProgram::addShader(const Shader &shader)
{
    glAttachShader(m_id, shader.getId());
}

unsigned int ShaderProgram::getUniformByName(const char *name)
{
    return glGetUniformLocation(m_id, name);
}

void ShaderProgram::setUniform(unsigned int id, const glm::mat4 &mat)
{
    glUniformMatrix4fv(id, 1, GL_FALSE, glm::value_ptr(mat));
}
