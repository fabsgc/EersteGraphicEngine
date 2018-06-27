#pragma once

#include "RenderPipeline.h"
#include "EventManager.h"

namespace ege
{
    RenderPipeline::RenderPipeline()
        : _renderAPI(gRenderAPI()) 
        , _window(gWindow())
        , _width(0)
        , _height(0)
    {}

    void RenderPipeline::Initialise(SPtr<Scene> scene)
    {
        _scene = scene;

        gEventManager().Suscribe("WINDOW_RESIZED", std::bind(&RenderPipeline::OnResize, this));
        gEventManager().Suscribe("WINDOW_FULLSCREEN", std::bind(&RenderPipeline::OnResize, this));

        _width = _window.GetWindowWidth();
        _height = _window.GetWindowHeight();
    }
}