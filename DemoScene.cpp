#include <imgui/imgui.h>
#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Engine.h"
#include "Scene.h"
#include "Window.h"
#include "renderer/Shader.h"
#include "renderer/Camera.h"
#include "renderer/ShaderProgram.h"

class CameraConfigWindow : public Engine::Window
{
public:
    CameraConfigWindow()
            : Window("Camera Config"), x(10.0), y(0.0), z(1.0)
    {}

protected:
    void renderContents() override
    {
        ImGui::Text("Camera Position:");
        ImGui::SliderFloat("X", &x, -80.0, 80.0);
        ImGui::SliderFloat("Y", &y, -80.0, 80.0);
        ImGui::SliderFloat("Z", &z, 1.0, 100.0);
    }

public:
    float x, y, z;
};

class DemoScene : public Engine::Scene
{
private:
    Engine::Renderer::ShaderProgram floorShader;
    unsigned int mvpUniform;
    std::shared_ptr<CameraConfigWindow> configWindow;

public:
    DemoScene()
            : Scene(std::make_shared<Engine::Renderer::Camera>(glm::vec3(0.0, 3.0, 5.0))),
              configWindow(std::make_shared<CameraConfigWindow>())
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
        getCamera()->setCameraPosition(glm::vec3(configWindow->x, configWindow->y, configWindow->z));
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
