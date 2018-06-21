#pragma once

#include "PrerequisitesCore.h"
#include "IDrawable.h"

namespace ege
{
    class RenderPipeline : public IDrawable
    {
    public:
        RenderPipeline() {};
        virtual ~RenderPipeline() {};
        virtual void Draw() = 0;
    };
}