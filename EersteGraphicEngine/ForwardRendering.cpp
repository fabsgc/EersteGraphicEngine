#pragma once

#include "ForwardRendering.h"
#include "ShaderManager.h"
#include "ModelManager.h"

#include "OrthographicCamera.h"

namespace ege
{
    ForwardRendering::ForwardRendering()
        : RenderPipeline()
        , _finalTexture(nullptr)
        , _renderTexture(nullptr)
        , _specularTexture(nullptr)
        , _normalTexture(nullptr)
        , _depthTexture(nullptr)
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

        _metaDataTargets[0] = _specularTexture->GetRenderTargetView();
        _metaDataTargets[1] = _normalTexture->GetRenderTargetView();
        _metaDataTargets[2] = _depthTexture->GetRenderTargetView();

        _quadShader = gShaderManager().GetPtr("quad");
        SPtr<ConstantBufferElement> quadConstantBuffer = _renderAPI.GetConstantBufferPtr(ConstantBufferType::QUAD);
        _quadShader->InsertConstantBuffer(0, quadConstantBuffer);

        gModelManager().Get("quad", _quad);
    }

    void ForwardRendering::Draw()
    {
        DrawMetaData();
        DrawRender();
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

        _metaDataTargets[0] = _specularTexture->GetRenderTargetView();
        _metaDataTargets[1] = _normalTexture->GetRenderTargetView();
        _metaDataTargets[2] = _depthTexture->GetRenderTargetView();
    }

    void ForwardRendering::SetMetaDataTargets()
    {
        ID3D11DeviceContext* context = _renderAPI.GetDevice()->GetImmediateContext();
        context->OMSetRenderTargets(FORWARD_DATA_RENDER_TARGET, _metaDataTargets, _renderAPI.GetDepthStencilView());
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

    void ForwardRendering::ClearMetaDataTargets()
    {
        ID3D11DeviceContext* context = _renderAPI.GetDevice()->GetImmediateContext();

        for (int i = 0; i < FORWARD_DATA_RENDER_TARGET; i++)
        {
            context->ClearRenderTargetView(_metaDataTargets[i], reinterpret_cast<const float*>(&Colors::Black));
        }
    }

    void ForwardRendering::ClearRenderTarget()
    {
        ID3D11DeviceContext* context = _renderAPI.GetDevice()->GetImmediateContext();
        context->ClearRenderTargetView(&*_renderTexture->GetRenderTargetView(), reinterpret_cast<const float*>(&Colors::Yellow));
    }

    void ForwardRendering::ClearFinalTarget()
    {
        ID3D11DeviceContext* context = _renderAPI.GetDevice()->GetImmediateContext();
        //context->ClearRenderTargetView(&*_finalTexture->GetRenderTargetView(), reinterpret_cast<const float*>(&Colors::LightSteelBlue));
        context->ClearRenderTargetView(&*_renderAPI.GetRenderTargetView(), reinterpret_cast<const float*>(&Colors::LightSteelBlue));
    }

    void ForwardRendering::DrawMetaData()
    {
        _renderAPI.ClearDepthStencilView();
        SetMetaDataTargets();
        ClearMetaDataTargets();

        _scene->DrawMetaData();
    }

    void ForwardRendering::DrawRender()
    {
        _renderAPI.ClearDepthStencilView();
        _renderAPI.ClearRenderTargetView();
        SetRenderTarget();
        ClearRenderTarget();

        _scene->Draw();
    }

    void ForwardRendering::DrawFinal()
    {
        _renderAPI.ClearDepthStencilView();
        SetFinalTarget();
        ClearFinalTarget();

        _renderAPI.TurnZBufferOff();

        OrthographicCamera camera;

        ID3D11DeviceContext* context = _renderAPI.GetDevice()->GetImmediateContext();

        XMFLOAT4X4 projection = camera.GetProjection();
        XMFLOAT4X4 view = camera.GetView();
        XMFLOAT4X4 world; XMStoreFloat4x4(&world, XMMatrixIdentity());

        SPtr<ConstantBufferElement> quadConstantBuffer = _renderAPI.GetConstantBufferPtr(ConstantBufferType::QUAD);
        QuadConstantBuffer* bufferUpdate = (QuadConstantBuffer*)&*quadConstantBuffer->UpdateBuffer;

        XMMATRIX V = XMLoadFloat4x4(&view);
        XMMATRIX P = XMLoadFloat4x4(&projection);
        XMMATRIX W = XMLoadFloat4x4(&world);

        bufferUpdate->View = XMMatrixTranspose(V);
        bufferUpdate->Projection = XMMatrixTranspose(P);
        bufferUpdate->World = XMMatrixTranspose(W);

        context->UpdateSubresource(quadConstantBuffer->Buffer, 0, nullptr, bufferUpdate, 0, 0);
        ID3D11ShaderResourceView* resourceView = _renderTexture->GetShaderResourceView();
        context->PSSetShaderResources(0, 1, &resourceView);

        _quadShader->Apply();
        _quad.Draw();

        _renderAPI.TurnZBufferOn();
    }
}