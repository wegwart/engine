#include "App.h"
#include "DemoWindow.h"
#include <spdlog/spdlog.h>

class MySandbox : public engine::App
{
public:
    MySandbox() = default;
};

int main()
{
    spdlog::set_level(spdlog::level::debug);
    
    MySandbox sandbox;
    sandbox.addWindow(std::make_shared<DemoWindow>());
    sandbox.exec();

    return 0;
}