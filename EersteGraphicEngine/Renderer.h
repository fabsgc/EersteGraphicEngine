#pragma once

#include "PrerequisitesCore.h"
#include "IComponentHandler.h"

namespace ege
{
    class Renderer : public IModule<Renderer>, public IComponentHandler
    {
    public:
        Renderer() {};
        ~Renderer() {};
        void OnStartUp() override;
        void OnShutDown() override {};

    private:
        Renderer(Renderer const&) = delete;
        Renderer& operator=(Renderer const&) = delete;
    };

    Renderer& gRenderer();
    Renderer* gRendererPtr();
}