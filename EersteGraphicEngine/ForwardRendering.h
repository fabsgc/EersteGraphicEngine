#pragma once

#include "PrerequisitesCore.h"
#include "RenderPipeline.h"
#include "RenderTexture.h"
#include "RenderAPI.h"
#include "Shader.h"
#include "Scene.h"

#include "Geometry.h"

#define FORWARD_DATA_RENDER_TARGET 4

namespace ege
{
    class ForwardRendering : public RenderPipeline
    {
    public:
        ForwardRendering();
        ~ForwardRendering();

        virtual void Initialise(SPtr<Scene> scene) override;
        virtual void Draw() override;
        virtual void Update() override;
        virtual void OnResize() override;

    protected:
        void CreateTextures();
        void CreateDepthStencil();
        void ClearDepthStencil();
        void CreateCamera();
        void CreateQuad();

        void SetMetaDataTargets();
        void SetRenderTarget();
        void SetEffectTarget();
        void SetFinalTarget();

        void ClearMetaDataTargets();
        void ClearRenderTarget();
        void ClearEffectTarget();
        void ClearFinalTarget();

        void DrawMetaData();
        void DrawRender();
        void DrawEffects();
        void DrawFinal();

    protected:
        SPtr<RenderTexture>      _finalTexture;
        SPtr<RenderTexture>      _renderTexture;
        SPtr<RenderTexture>      _specularTexture;
        SPtr<RenderTexture>      _normalTexture;
        SPtr<RenderTexture>      _depthTexture;

        ID3D11RenderTargetView*  _metaDataTargets[FORWARD_DATA_RENDER_TARGET];

        SPtr<Shader>             _quadShader;
        SPtr<QuadScreenCamera>   _camera;
        SPtr<Geometry>           _quad;

        ID3D11DepthStencilView*  _depthStencilView;
        ID3D11Texture2D*         _depthStencilBuffer;
    };
}