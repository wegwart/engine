#include <iostream>

#include "App.h"
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
    //sandbox.setFullscreen();
    sandbox.exec();

    return 0;
}