#pragma once

#include "PrerequisitesCore.h"
#include "RenderPipeline.h"
#include "RenderTexture.h"
#include "Scene.h"

namespace ege
{
    class DeferredRendering : public RenderPipeline
    {
    public:
        DeferredRendering();
        ~DeferredRendering() {};
        
        virtual void Initialise(SPtr<Scene> scene) override;
        virtual void Draw() override;
        virtual void Update() override;
        virtual void OnResize() override;

    protected:        
    };
}