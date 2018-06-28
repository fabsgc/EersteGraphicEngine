#pragma once

#include "DeferredRendering.h"

namespace ege
{
    DeferredRendering::DeferredRendering()
        : RenderPipeline()
    {}

    void DeferredRendering::Initialise(SPtr<Scene> scene)
    {
        RenderPipeline::Initialise(scene);
    }

    void DeferredRendering::Draw()
    {
    }

    void DeferredRendering::Update()
    {
    }

    void DeferredRendering::OnResize()
    {
        _width = _window.GetWindowWidth();
        _height = _window.GetWindowHeight();
    }
}