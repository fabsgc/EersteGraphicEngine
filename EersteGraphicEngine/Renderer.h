#pragma once

#include "PrerequisitesCore.h"
#include "IComponentHandler.h"
#include "IUpdatable.h"
#include "IDrawable.h"

namespace ege
{
    class Renderer : public IModule<Renderer>, public IComponentHandler, public IUpdatable, public IDrawable
    {
    public:
        Renderer() {};
        ~Renderer() {};
        void OnStartUp() override;
        void OnShutDown() override {};

        void Update() override {};
        void Draw() override {};

    protected:
        Renderer(Renderer const&) = delete;
        Renderer& operator=(Renderer const&) = delete;
    };

    Renderer& gRenderer();
    Renderer* gRendererPtr();
}