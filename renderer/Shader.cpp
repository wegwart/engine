//
// Created by alex on 2/14/23.
//

#include "Shader.h"
#include <GL/glew.h>
#include <spdlog/spdlog.h>
#include <fstream>
#include <sstream>

using namespace Engine::Renderer;

Shader::Shader(const std::string &filename, ShaderType shaderType)
        : m_filename(filename), m_id(glCreateShader(shaderType))
{
}

Shader::~Shader()
{
    glDeleteShader(m_id);
}

bool Shader::compile()
{
    std::string sourceCode;
    {
        try
        {
            std::ifstream sourceCodeFile(m_filename);
            std::stringstream sourceCodeBuffer;
            sourceCodeBuffer << sourceCodeFile.rdbuf();
            sourceCode = sourceCodeBuffer.str();
        } catch (std::exception &e)
        {
            spdlog::error("cannot load shader from file: {}", e.what());
            return false;
        }
    }

    const char *sourceCodePtr = sourceCode.c_str();
    glShaderSource(m_id, 1, &sourceCodePtr, nullptr);
    glCompileShader(m_id);

    int success;
    char messageBuffer[512];
    glGetShaderiv(m_id, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(m_id, sizeof(messageBuffer), nullptr, messageBuffer);
        spdlog::error("OpenGL shader compilation failed: {}", messageBuffer);
        return false;
    }

    return true;
}

unsigned int Shader::getId() const
{
    return m_id;
}
