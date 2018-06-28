#pragma once

#include "ForwardRendering.h"
#include "ShaderManager.h"

namespace ege
{
    ForwardRendering::ForwardRendering()
        : RenderPipeline()
        , _finalTexture(nullptr)
        , _renderTexture(nullptr)
        , _specularTexture(nullptr)
        , _normalTexture(nullptr)
        , _depthTexture(nullptr)
        , _dataShader(nullptr)
        , _renderShader(nullptr)
    {}

    void ForwardRendering::Initialise(SPtr<Scene> scene)
    {
        RenderPipeline::Initialise(scene);

        _finalTexture    = ege_shared_ptr_new<RenderTexture>(_width, _height);
        _renderTexture   = ege_shared_ptr_new<RenderTexture>(_width, _height);
        _specularTexture = ege_shared_ptr_new<RenderTexture>(_width, _height);
        _normalTexture   = ege_shared_ptr_new<RenderTexture>(_width, _height);
        _depthTexture    = ege_shared_ptr_new<RenderTexture>(_width, _height);
        
        _renderTexture->Initialise();
        _specularTexture->Initialise();
        _normalTexture->Initialise();
        _depthTexture->Initialise();

        _dataTargets[0] = _specularTexture->GetRenderTargetView();
        _dataTargets[1] = _normalTexture->GetRenderTargetView();
        _dataTargets[2] = _depthTexture->GetRenderTargetView();

        _dataShader = gShaderManager().GetPtr("forward-data");
        _quadShader = gShaderManager().GetPtr("quad");
    }

    void ForwardRendering::Draw()
    {
        //DrawData();
        //DrawRender();
        DrawFinal();
    }

    void ForwardRendering::Update()
    {
    }

    void ForwardRendering::OnResize()
    {
        _width  = _window.GetWindowWidth();
        _height = _window.GetWindowHeight();

        _renderTexture->Resize(_width, _height);
        _specularTexture->Resize(_width, _height);
        _normalTexture->Resize(_width, _height);
        _depthTexture->Resize(_width, _height);

        _dataTargets[0] = _specularTexture->GetRenderTargetView();
        _dataTargets[1] = _normalTexture->GetRenderTargetView();
        _dataTargets[2] = _depthTexture->GetRenderTargetView();
    }

    void ForwardRendering::SetDataTargets()
    {
        ID3D11DeviceContext* context = _renderAPI.GetDevice()->GetImmediateContext();
        context->OMSetRenderTargets(FORWARD_DATA_RENDER_TARGET, _dataTargets, _renderAPI.GetDepthStencilView());
    }

    void ForwardRendering::SetRenderTarget()
    {
        ID3D11DeviceContext* context = _renderAPI.GetDevice()->GetImmediateContext();
        ID3D11RenderTargetView* renderTargetView = _renderTexture->GetRenderTargetView();
        context->OMSetRenderTargets(1, &renderTargetView, _renderAPI.GetDepthStencilView());
    }

    void ForwardRendering::SetFinalTarget()
    {
        ID3D11DeviceContext* context = _renderAPI.GetDevice()->GetImmediateContext();
        //ID3D11RenderTargetView* renderTargetView = _finalTexture->GetRenderTargetView();
        ID3D11RenderTargetView* renderTargetView = _renderAPI.GetRenderTargetView();
        context->OMSetRenderTargets(1, &renderTargetView, _renderAPI.GetDepthStencilView());
    }

    void ForwardRendering::ClearDataTargets()
    {
        ID3D11DeviceContext* context = _renderAPI.GetDevice()->GetImmediateContext();

        for (int i = 0; i < FORWARD_DATA_RENDER_TARGET; i++)
        {
            context->ClearRenderTargetView(_dataTargets[i], reinterpret_cast<const float*>(&Colors::Magenta));
        }
    }

    void ForwardRendering::ClearRenderTarget()
    {
        ID3D11DeviceContext* context = _renderAPI.GetDevice()->GetImmediateContext();
        context->ClearRenderTargetView(&*_renderTexture->GetRenderTargetView(), reinterpret_cast<const float*>(&Colors::Magenta));
    }

    void ForwardRendering::ClearFinalTarget()
    {
        ID3D11DeviceContext* context = _renderAPI.GetDevice()->GetImmediateContext();
        //context->ClearRenderTargetView(&*_finalTexture->GetRenderTargetView(), reinterpret_cast<const float*>(&Colors::Magenta));
        context->ClearRenderTargetView(&*_renderAPI.GetRenderTargetView(), reinterpret_cast<const float*>(&Colors::Magenta));
    }

    void ForwardRendering::DrawData()
    {
        _renderAPI.ClearDepthStencilView();
        SetDataTargets();
        ClearDataTargets();
        
        _dataShader->Apply();
    }

    void ForwardRendering::DrawRender()
    {
        _renderAPI.ClearDepthStencilView();
        SetRenderTarget();
        ClearRenderTarget();
    }

    void ForwardRendering::DrawFinal()
    {
        _renderAPI.ClearDepthStencilView();
        SetFinalTarget();
        ClearRenderTarget();

        _scene->Draw();
    }
}