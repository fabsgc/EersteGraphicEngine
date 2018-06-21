#pragma once

#include "PrerequisitesCore.h"
#include "RenderPipeline.h"

namespace ege
{
    class DeferredRendering : public RenderPipeline
    {
    public:
        DeferredRendering() {};
        ~DeferredRendering() {};
        virtual void Draw() override {};
    };
}