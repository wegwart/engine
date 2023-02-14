//
// Created by alex on 2/14/23.
//

#pragma once

namespace Engine {
    class Scene
    {
    public:
        Scene() = default;

        virtual ~Scene() = default;

        virtual void update()
        {}

        virtual void render()
        {}


    };
}