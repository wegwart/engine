#include <imgui/imgui.h>
#include <GL/glew.h>
#include <glm/glm.hpp>

#include <engine/Engine.h>
#include <engine/Scene.h>
#include <engine/Window.h>
#include <engine/Shader.h>
#include <engine/Camera.h>
#include <engine/ShaderProgram.h>

class DemoSceneConfigWindow : public Engine::Window
{
public:
    DemoSceneConfigWindow()
            : Window("Demo Scene Config Window")
              , m_cameraPos{1.0, 10.0, 3.0}
              , m_cameraLookAt{0.0, 0.0, 0.0}
    {}

protected:
    void renderContents() override
    {
        auto &io = ImGui::GetIO();
        ImGui::Text("Average real frame rate: %f FPS", io.Framerate);
        ImGui::SliderFloat("Framerate limit", &Engine::framerate(), 1.0, 60.0);
        ImGui::Separator();
        ImGui::SliderFloat3("Camera Position", (float *) &m_cameraPos, -20.0, 20.0);
        ImGui::SliderFloat3("Camera Look-At", (float *) &m_cameraLookAt, -20.0, 20.0);
    }

public:
    float m_cameraPos[3];
    float m_cameraLookAt[3];
};

class DemoScene : public Engine::Scene
{
private:
    Engine::Renderer::ShaderProgram floorShader;
    unsigned int mvpUniform;
    std::shared_ptr<DemoSceneConfigWindow> configWindow;

public:
    DemoScene()
            : Scene(std::make_shared<Engine::Renderer::Camera>(glm::vec3(0.0, 3.0, 5.0)))
              , configWindow(std::make_shared<DemoSceneConfigWindow>())
    {
        Engine::Renderer::Shader vertexShader("../shader/vert.glsl",
                                              Engine::Renderer::Shader::ShaderType::VertexShader);
        auto success = vertexShader.compile();
        assert(success == true);
        floorShader.addShader(vertexShader);

        Engine::Renderer::Shader fragShader("../shader/frag.glsl",
                                            Engine::Renderer::Shader::ShaderType::FragmentShader);
        success = fragShader.compile();
        assert(success == true);
        floorShader.addShader(fragShader);

        floorShader.link();
        floorShader.bind();

        mvpUniform = floorShader.getUniformByName("u_MVP");
    }

    void update() override
    {
        getCamera()->setPosition(
                glm::vec3(configWindow->m_cameraPos[0], configWindow->m_cameraPos[1], configWindow->m_cameraPos[2]));
        getCamera()->setLookAtPoint(
                glm::vec3(configWindow->m_cameraLookAt[0], configWindow->m_cameraLookAt[1],
                          configWindow->m_cameraLookAt[2]));
    }

    void render(const glm::mat4 &projectionMatrix) override
    {
        // Create a tiled floor that is spans a square area of 100 m2
        // For that we just generate some vertices and let a custom
        // geometry shader expand this to a proper triangle mesh.

        floorShader.bind();

        floorShader.setUniform(mvpUniform, projectionMatrix * getViewMatrix());

        glBegin(GL_TRIANGLES);
        for (int x = -50; x < 50; x++)
        {
            for (int y = -50; y < 50; y++)
            {
                float color = ((x % 2) * (x % 2) == (y % 2) * (y % 2)) ? 1.0 : -1.0;

                glVertex3f(x, y, color);
                glVertex3f(x + 1, y, color);
                glVertex3f(x + 1, y + 1, color);

                glVertex3f(x, y, color);
                glVertex3f(x, y + 1, color);
                glVertex3f(x + 1, y + 1, color);
            }
        }
        glEnd();
    }
};

namespace EngineApp {
    void onInit()
    {
        Engine::setScene(std::make_shared<DemoScene>());
    }
}
