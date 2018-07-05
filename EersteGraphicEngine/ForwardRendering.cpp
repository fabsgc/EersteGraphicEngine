#pragma once

#include "ForwardRendering.h"
#include "ShaderManager.h"
#include "ModelManager.h"

#include "QuadScreenCamera.h"
#include "Model.h"
#include "Node.h"

namespace ege
{
    ForwardRendering::ForwardRendering()
        : RenderPipeline()
        , _finalTexture(nullptr)
        , _renderTexture(nullptr)
        , _specularTexture(nullptr)
        , _normalTexture(nullptr)
        , _depthTexture(nullptr)
        , _depthStencilView(nullptr)
        , _depthStencilBuffer(nullptr)
    {}

    ForwardRendering::~ForwardRendering()
    {
        SafeReleaseCom(_depthStencilView);
        SafeReleaseCom(_depthStencilBuffer);
    }

    void ForwardRendering::Initialise(SPtr<Scene> scene)
    {
        RenderPipeline::Initialise(scene);

        CreateTextures();
        CreateDepthStencil();
        CreateCamera();
        CreateQuad();
    }

    void ForwardRendering::CreateTextures()
    {
        _finalTexture = ege_shared_ptr_new<RenderTexture>(_width, _height);
        _renderTexture = ege_shared_ptr_new<RenderTexture>(_width, _height);
        _specularTexture = ege_shared_ptr_new<RenderTexture>(_width, _height);
        _normalTexture = ege_shared_ptr_new<RenderTexture>(_width, _height);
        _depthTexture = ege_shared_ptr_new<RenderTexture>(_width, _height);

        _renderTexture->Initialise();
        _specularTexture->Initialise();
        _normalTexture->Initialise();
        _depthTexture->Initialise();

        _metaDataTargets[0] = _specularTexture->GetRenderTargetView();
        _metaDataTargets[1] = _normalTexture->GetRenderTargetView();
        _metaDataTargets[2] = _depthTexture->GetRenderTargetView();
    }

    void ForwardRendering::CreateDepthStencil()
    {
        HRESULT hr = S_OK;
        ID3D11Device* device = _renderAPI.GetDevice()->GetD3D11Device();
        D3D11_TEXTURE2D_DESC depthStencilDesc;
        ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));

        depthStencilDesc.Width = _width;
        depthStencilDesc.Height = _height;
        depthStencilDesc.MipLevels = 1;
        depthStencilDesc.ArraySize = 1;
        depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
        depthStencilDesc.SampleDesc.Count = 1;
        depthStencilDesc.SampleDesc.Quality = 0;
        depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
        depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
        depthStencilDesc.CPUAccessFlags = 0;
        depthStencilDesc.MiscFlags = 0;

        D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
        ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));

        depthStencilViewDesc.Format = depthStencilDesc.Format;
        depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
        depthStencilViewDesc.Flags = 0;
        depthStencilViewDesc.Texture2D.MipSlice = 0;

        hr = device->CreateTexture2D(&depthStencilDesc, nullptr, &_depthStencilBuffer);
        EGE_ASSERT_ERROR(SUCCEEDED(hr), "Can't create depth stencil buffer");

        device->CreateDepthStencilView(_depthStencilBuffer, &depthStencilViewDesc, &_depthStencilView);
        EGE_ASSERT_ERROR(SUCCEEDED(hr), "Can't create depth stencil view");
    }

    void ForwardRendering::ClearDepthStencil()
    {
        ID3D11DeviceContext* context = _renderAPI.GetDevice()->GetImmediateContext();
        context->ClearDepthStencilView(_depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
    }

    void ForwardRendering::CreateCamera()
    {
        _camera = ege_shared_ptr_new<QuadScreenCamera>();
        ID3D11DeviceContext* context = _renderAPI.GetDevice()->GetImmediateContext();
        SPtr<ConstantBufferElement> quadConstantBuffer = _renderAPI.GetConstantBufferPtr(ConstantBufferType::QUAD);

        XMFLOAT4X4 projection = _camera->GetProjection();
        XMFLOAT4X4 view = _camera->GetView();
        XMFLOAT4X4 world; XMStoreFloat4x4(&world, XMMatrixIdentity());

        QuadConstantBuffer* bufferUpdate = (QuadConstantBuffer*)&*quadConstantBuffer->UpdateBuffer;

        XMMATRIX V = XMLoadFloat4x4(&view);
        XMMATRIX P = XMLoadFloat4x4(&projection);
        XMMATRIX W = XMLoadFloat4x4(&world);

        bufferUpdate->View = XMMatrixTranspose(V);
        bufferUpdate->Projection = XMMatrixTranspose(P);
        bufferUpdate->World = XMMatrixTranspose(W);

        context->UpdateSubresource(quadConstantBuffer->Buffer, 0, nullptr, bufferUpdate, 0, 0);
    }

    void ForwardRendering::CreateQuad()
    {
        _quad = ege_shared_ptr_new<Geometry>();
        _quadShader = gShaderManager().GetPtr("quad");
        gModelManager().Get("quad", *_quad);

        SPtr<ConstantBufferElement> quadConstantBuffer = _renderAPI.GetConstantBufferPtr(ConstantBufferType::QUAD);
        _quadShader->InsertConstantBuffer(0, quadConstantBuffer);
    }

    void ForwardRendering::Draw()
    {
        DrawMetaData();
        DrawRender();
        //DrawEffects();
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

        CreateDepthStencil();
    }

    void ForwardRendering::SetMetaDataTargets()
    {
        ID3D11DeviceContext* context = _renderAPI.GetDevice()->GetImmediateContext();
        context->OMSetRenderTargets(FORWARD_DATA_RENDER_TARGET, _metaDataTargets, _depthStencilView);
    }

    void ForwardRendering::SetRenderTarget()
    {
        ID3D11DeviceContext* context = _renderAPI.GetDevice()->GetImmediateContext();
        ID3D11RenderTargetView* renderTargetView = _renderTexture->GetRenderMSTargetView();
        context->OMSetRenderTargets(1, &renderTargetView, _renderAPI.GetDepthStencilView());
    }

    void ForwardRendering::SetEffectTarget()
    {
        ID3D11DeviceContext* context = _renderAPI.GetDevice()->GetImmediateContext();
        ID3D11RenderTargetView* renderTargetView = _renderTexture->GetRenderMSTargetView();
        context->OMSetRenderTargets(1, &renderTargetView, _renderAPI.GetDepthStencilView());
    }

    void ForwardRendering::SetFinalTarget()
    {
        ID3D11DeviceContext* context = _renderAPI.GetDevice()->GetImmediateContext();
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
        context->ClearRenderTargetView(&*_renderTexture->GetRenderMSTargetView(), reinterpret_cast<const float*>(&Colors::LightSteelBlue));
    }

    void ForwardRendering::ClearEffectTarget()
    {
        ID3D11DeviceContext* context = _renderAPI.GetDevice()->GetImmediateContext();
        context->ClearRenderTargetView(&*_renderTexture->GetRenderMSTargetView(), reinterpret_cast<const float*>(&Colors::LightSteelBlue));
    }

    void ForwardRendering::ClearFinalTarget()
    {
        ID3D11DeviceContext* context = _renderAPI.GetDevice()->GetImmediateContext();
        context->ClearRenderTargetView(&*_renderAPI.GetRenderTargetView(), reinterpret_cast<const float*>(&Colors::LightSteelBlue));
    }

    void ForwardRendering::DrawMetaData()
    {
        ClearDepthStencil();
        SetMetaDataTargets();
        ClearMetaDataTargets();

        _scene->DrawMetaData();

        //ID3D11DeviceContext* context = _renderAPI.GetDevice()->GetImmediateContext();
        //ID3D11RenderTargetView* nullViews[FORWARD_DATA_RENDER_TARGET] = { nullptr, nullptr, nullptr };
        //context->OMSetRenderTargets(FORWARD_DATA_RENDER_TARGET, nullViews, nullptr);
    }

    void ForwardRendering::DrawRender()
    {
        _renderAPI.ClearDepthStencilView();
        SetRenderTarget();
        ClearRenderTarget();

        //_scene->Draw();

        SPtr<Camera> camera = _scene->GetActiveCamera();
        Map<String, SPtr<Node>>& nodes = _scene->GetNodes();
        Map<String, SPtr<Light>>& lights = _scene->GetLights();
        SPtr<AmbientLight> ambientLight = _scene->GetAmbientLight();

        ID3D11DeviceContext* context = _renderAPI.GetDevice()->GetImmediateContext();

        SPtr<ConstantBufferElement> lightConstantBuffer = _renderAPI.GetConstantBufferPtr(ConstantBufferType::LIGHT);
        LightConstantBuffer* lightConstantBufferUpdate = (LightConstantBuffer*)&*lightConstantBuffer->UpdateBuffer;

        SPtr<ConstantBufferElement> objectConstantBuffer = _renderAPI.GetConstantBufferPtr(ConstantBufferType::OBJECT);
        ObjectConstantBuffer* objectConstantBufferUpdate = (ObjectConstantBuffer*)&*objectConstantBuffer->UpdateBuffer;

        lightConstantBufferUpdate->LightIndex = 0;

        _scene->DrawCamera();

        if (ambientLight != nullptr && ambientLight->IsEnabled())
        {
            ambientLight->Draw();
        }

        for (auto node : nodes)
        {
            Map<String, SPtr<Node>>& children = node.second->GetChildren();

            if (node.second->GetType() == NodeType::Model)
            {
                SPtr<Model> model = dynamic_cast<Model*>(node.second);
                LightMode lightMode = model->GetLightMode();
            }

            for (auto child : children)
            {
                if (child.second->GetType() != NodeType::Camera && child.second->GetType() != NodeType::Light)
                {
                    //child.second->Draw();
                }
            }
        }



        //ID3D11DeviceContext* context = _renderAPI.GetDevice()->GetImmediateContext();
        //ID3D11RenderTargetView* nullViews[1] = { nullptr };
        //context->OMSetRenderTargets(1, nullViews, nullptr);
    }

    void ForwardRendering::DrawEffects()
    {
        /*_renderAPI.ClearDepthStencilView();
        SetEffectTarget();
        ClearEffectTarget();*/
    }

    void ForwardRendering::DrawFinal()
    {
        _renderAPI.ClearDepthStencilView();
        SetFinalTarget();
        ClearFinalTarget();

        _renderAPI.TurnZBufferOff();

        ID3D11DeviceContext* context = _renderAPI.GetDevice()->GetImmediateContext();

        _renderTexture->BoundNonMsTexture();

        ID3D11ShaderResourceView* resourceView = _renderTexture->GetShaderResourceView();
        context->PSSetShaderResources(7, 1, &resourceView);

        _quadShader->Apply();
        _quad->Draw();

        _renderAPI.TurnZBufferOn();

        //ID3D11ShaderResourceView* null[] = { nullptr, nullptr, nullptr };
        //context->PSSetShaderResources(0, 3, null);
    }
}