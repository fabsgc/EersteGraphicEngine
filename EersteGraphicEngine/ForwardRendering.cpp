#pragma once

#include "ForwardRendering.h"

namespace ege
{
    ForwardRendering::ForwardRendering()
        : RenderPipeline()
    {}

    void ForwardRendering::Initialise(SPtr<Scene> scene)
    {
        RenderPipeline::Initialise(scene);

        _renderTexture   = ege_shared_ptr_new<RenderTexture>(_width, _height);
        _depthTexture    = ege_shared_ptr_new<RenderTexture>(_width, _height);
        _SpecularTexture = ege_shared_ptr_new<RenderTexture>(_width, _height);
        _normalTexture   = ege_shared_ptr_new<RenderTexture>(_width, _height);

        _renderTexture->Initialise();
        _depthTexture->Initialise();
        _SpecularTexture->Initialise();
        _normalTexture->Initialise();
    }

    void ForwardRendering::Draw()
    {
    }

    void ForwardRendering::Update()
    {
    }

    void ForwardRendering::OnResize()
    {
        _width = _window.GetWindowWidth();
        _height = _window.GetWindowHeight();

        _renderTexture->Resize(_width, _height);
        _depthTexture->Resize(_width, _height);
        _SpecularTexture->Resize(_width, _height);
        _normalTexture->Resize(_width, _height);
    }
}