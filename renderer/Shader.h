//
// Created by alex on 2/14/23.
//

#pragma once

#include <string>
#include <GL/glew.h>

namespace Engine {
    namespace Renderer {

        class Shader
        {
            friend class ShaderProgram;

        public:
            enum ShaderType
            {
                VertexShader = GL_VERTEX_SHADER,
                GeometryShader = GL_GEOMETRY_SHADER,
                FragmentShader = GL_FRAGMENT_SHADER,
            };

            explicit Shader(const std::string &filename, ShaderType shaderType);

            Shader(const Shader &) = delete;

            ~Shader();

            bool compile();

        protected:
            unsigned int getId() const;

        private:
            std::string m_filename;
            unsigned int m_id;
        };

    } // Engine
} // Renderer
