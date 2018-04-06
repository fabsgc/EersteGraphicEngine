#pragma once

#include "PrerequisitesCore.h"
#include "IComponentHandler.h"

namespace ege
{
    class RenderAPI : public IModule<RenderAPI>, public IComponentHandler
    {
    public:
        RenderAPI() {};
        ~RenderAPI() {};
        void OnStartUp() override;
        void OnShutDown() override {};

        void Initialise();
        void Reset();

    private:
        RenderAPI(RenderAPI const&) = delete;
        RenderAPI& operator=(RenderAPI const&) = delete;
    };

    RenderAPI& gRenderAPI();
    RenderAPI* gRenderAPIPtr();
}