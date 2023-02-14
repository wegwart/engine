#include "App.h"
#include "Scene.h"
#include <spdlog/spdlog.h>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtx/matrix_transform_2d.hpp>

#include "renderer/Shader.h"
#include "renderer/ShaderProgram.h"

class MySandbox : public Engine::App
{
public:
    MySandbox() = default;
};

class DemoScene : public Engine::Scene
{
public:
    DemoScene()
            : m_angle(0.0)
    {

    }

    void update() override
    {
        m_angle += 0.1;
    }

    void render() override
    {
        auto p1 = glm::vec3(-0.5f, -0.5f, 1.0f);
        auto p2 = glm::vec3(0.0f, 0.5f, 1.0f);
        auto p3 = glm::vec3(0.5f, -0.5f, 1.0f);

        auto rotmat = glm::rotate(glm::mat3(1.0f), m_angle);
        p1 = rotmat * p1;
        p2 = rotmat * p2;
        p3 = rotmat * p3;

        glBegin(GL_TRIANGLES);
        glVertex2f(p1.x, p2.y);
        glVertex2f(p2.x, p2.y);
        glVertex2f(p3.x, p3.y);
        glEnd();
    }

private:
    float m_angle;
};

int main()
{
    spdlog::set_level(spdlog::level::debug);

    MySandbox sandbox;

    Engine::Renderer::ShaderProgram shaders;
    {
        Engine::Renderer::Shader fragShader("../shader/frag.glsl",
                                            Engine::Renderer::Shader::ShaderType::FragmentShader);
        auto success = fragShader.compile();
        assert(success == true);
        shaders.addShader(fragShader);
        shaders.link();
    }
    shaders.bind();

    sandbox.setScene(std::make_shared<DemoScene>());
    sandbox.exec();

    return 0;
}