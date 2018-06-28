#pragma once

#include "PrerequisitesCore.h"
#include "RenderPipeline.h"
#include "RenderTexture.h"
#include "RenderAPI.h"
#include "Shader.h"
#include "Scene.h"

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
        void SetDataTargets();
        void SetRenderTarget();
        void SetFinalTarget();

        void ClearDataTargets();
        void ClearRenderTarget();
        void ClearFinalTarget();

        void DrawData();
        void DrawRender();
        void DrawFinal();

    protected:
        SPtr<RenderTexture>     _finalTexture;
        SPtr<RenderTexture>     _renderTexture;
        SPtr<RenderTexture>     _specularTexture;
        SPtr<RenderTexture>     _normalTexture;
        SPtr<RenderTexture>     _depthTexture;

        SPtr<Shader>            _dataShader;
        SPtr<Shader>            _renderShader;
        SPtr<Shader>            _quadShader;

        ID3D11RenderTargetView* _dataTargets[FORWARD_DATA_RENDER_TARGET];
    };
}