#pragma once

#include "PrerequisitesCore.h"
#include "RenderPipeline.h"
#include "RenderTexture.h"
#include "RenderAPI.h"
#include "Shader.h"
#include "Scene.h"

#include "Geometry.h"

#define FORWARD_DATA_RENDER_TARGET 3

namespace ege
{
    class ForwardRendering : public RenderPipeline
    {
    public:
        ForwardRendering();
        ~ForwardRendering() {};

        virtual void Initialise(SPtr<Scene> scene) override;
        virtual void Draw() override;
        virtual void Update() override;
        virtual void OnResize() override;

    protected:
        void SetMetaDataTargets();
        void SetRenderTarget();
        void SetFinalTarget();

        void ClearMetaDataTargets();
        void ClearRenderTarget();
        void ClearFinalTarget();

        void DrawMetaData();
        void DrawRender();
        void DrawFinal();

    protected:
        SPtr<RenderTexture>     _finalTexture;
        SPtr<RenderTexture>     _renderTexture;
        SPtr<RenderTexture>     _specularTexture;
        SPtr<RenderTexture>     _normalTexture;
        SPtr<RenderTexture>     _depthTexture;

        SPtr<Shader>            _quadShader;

        ID3D11RenderTargetView* _metaDataTargets[FORWARD_DATA_RENDER_TARGET];

        Geometry                _quad;

        XMMATRIX _world;
        XMMATRIX _view;
        XMMATRIX _projection;
    };
}