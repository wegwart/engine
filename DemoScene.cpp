#include <imgui/imgui.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include <engine/Engine.h>
#include <engine/Scene.h>
#include <engine/Window.h>
#include <engine/Camera.h>
#include <engine/ShaderProgram.h>

namespace EngineApp {

    /**
     *  DemoSceneConfigWindow inherits from Engine::Window so as soon
     *  as the object is constructed, a GUI window will be rendered.
     *  The config parameters in this class are updated every frame.
     */
    class DemoSceneConfigWindow : public Engine::Window
    {
    public:
        DemoSceneConfigWindow()
                : Window("Demo Scene Config Window")
                  , m_cameraPos{1.0, 10.0, 3.0}
                  , m_cameraLookAt{0.0, 0.0, 0.0}
        {}

    protected:
        /**
         * By overriding renderContents() we can control what should be
         * rendered inside the GUI window. For now: raw ImGui controls...
         * This should maybe be encapsulated in the future ?
         */
        void renderContents() override
        {
            auto &io = ImGui::GetIO();
            ImGui::Text("Average real frame rate: %f FPS", io.Framerate);
            ImGui::SliderFloat("Framerate limit", &Engine::framerateLimit(), 1.0, 60.0);
            ImGui::Separator();
            ImGui::SliderFloat3("Camera Position", (float *) &m_cameraPos, -20.0, 20.0);
            ImGui::SliderFloat3("Camera Look-At", (float *) &m_cameraLookAt, -20.0, 20.0);
        }

    public:
        float m_cameraPos[3];
        float m_cameraLookAt[3];
    };


    /**
     * The DemoScene object inherits from Engine::Scene which means it is
     * a render-able scene. Engine::setScene() sets the currently active scene.
     */
    class DemoScene : public Engine::Scene
    {
    public:
        DemoScene()
                : Scene(std::make_shared<Engine::Renderer::Camera>(glm::vec3()))
                  , config(std::make_shared<DemoSceneConfigWindow>())
        {
            // compile a vertex and a fragment shader and link them into
            // a single shader program that we can use
            m_gridFloorShaderProgram.compileAndLinkShaders("../shader/demoVertexShader.glsl",
                                                           "../shader/demoFragmentShader.glsl");

            // after the shader program has been linked we query the ID
            // of the u_MVP uniform so we can upload the MVP matrix later...
            u_mvp = m_gridFloorShaderProgram.getUniformByName("u_MVP");
        }

        void update() override
        {
            // at each frame update, we read the values from the configuration window
            // and update the camera's view matrix.

            getCamera()->setPosition(glm::vec3(config->m_cameraPos[0],
                                               config->m_cameraPos[1], config->m_cameraPos[2]));
            getCamera()->setLookAtPoint(glm::vec3(config->m_cameraLookAt[0],
                                                  config->m_cameraLookAt[1], config->m_cameraLookAt[2]));
        }

        void render(const glm::mat4 &projectionMatrix) override
        {
            // Compute the Model-View-Projection matrix and upload it to the shader
            // program on the GPU (model component has been left out for now)
            m_gridFloorShaderProgram.setUniform(u_mvp, projectionMatrix * getViewMatrix());

            // Create a tiled floor that is spans a square area of 100 m2
            // For that we just generate some vertices and let a custom
            // geometry shader expand this to a proper triangle mesh.

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

    private:
        unsigned int u_mvp;
        Engine::Renderer::ShaderProgram m_gridFloorShaderProgram;
        std::shared_ptr<DemoSceneConfigWindow> config;
    };

    /**
     * The onInit() function must be implemented by the user of the
     * framework to be used as an entry point to the application.
     */
    void onInit()
    {
        Engine::setScene(std::make_shared<DemoScene>());
    }
}
