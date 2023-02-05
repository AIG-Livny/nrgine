#pragma once

#include "scene/scene.h"

class Renderer{
    public:
        void Render(const std::unique_ptr<scene::Scene>& scene);
};