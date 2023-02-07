#include <iostream>

#include "App.h"

class MySandbox : public engine::App
{
public:
    MySandbox() = default;
};

int main()
{
    MySandbox sandbox;
    sandbox.exec();

    return 0;
}