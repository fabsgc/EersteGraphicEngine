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

        _diffuseTexture = ege_shared_ptr_new<RenderTexture>(_width, _height);
        _depthTexture = ege_shared_ptr_new<RenderTexture>(_width, _height);
        _SpecularTexture = ege_shared_ptr_new<RenderTexture>(_width, _height);
        _normalTexture = ege_shared_ptr_new<RenderTexture>(_width, _height);
        _lightTexture = ege_shared_ptr_new<RenderTexture>(_width, _height);
        _renderTexture = ege_shared_ptr_new<RenderTexture>(_width, _height);

        _diffuseTexture->Initialise();
        _depthTexture->Initialise();
        _SpecularTexture->Initialise();
        _normalTexture->Initialise();
        _lightTexture->Initialise();
        _renderTexture->Initialise();
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

        _diffuseTexture->Resize(_width, _height);
        _depthTexture->Resize(_width, _height);
        _SpecularTexture->Resize(_width, _height);
        _normalTexture->Resize(_width, _height);
        _lightTexture->Resize(_width, _height);
        _renderTexture->Resize(_width, _height);
    }
}