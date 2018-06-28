#pragma once

#include "PrerequisitesCore.h"

namespace ege
{
    struct ConstantBuffer
    {
    };

    struct FrameConstantBuffer : public ConstantBuffer
    {
        XMMATRIX View;
        XMMATRIX Projection;

        XMFLOAT3 CameraPosition;
        /* PADDING */ float    Padding1;

        FrameConstantBuffer()
        {}
    };

    struct ObjectConstantBuffer : public ConstantBuffer
    {
        XMMATRIX World;

        XMFLOAT4 SpecularColor;
        float    SpecularPower;
        float    EmitPower;
        BOOL     HasSpecular;
        BOOL     HasEmit;
        BOOL     HasDiffuseTexture;
        BOOL     HasSpecularTexture;
        BOOL     HasNormalTexture;
        /* PADDING */ float    Padding1;

        ObjectConstantBuffer()
            : SpecularColor(XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f))
            , SpecularPower(8.0f)
            , EmitPower(0.0f)
            , HasSpecular(true)
            , HasEmit(true)
            , HasDiffuseTexture(true)
            , HasSpecularTexture(true)
            , HasNormalTexture(true)
        {}
    };

    struct LightConstantBuffer : public ConstantBuffer
    {
        XMFLOAT4  AmbientColor;
        UINT      LightIndex;
        /* PADDING */ float    Padding1[3];
        LightDesc Lights[8];

        LightConstantBuffer()
            : AmbientColor(XMFLOAT4(1.0f, 1.0f, 1.0f, 0.2f))
        {}
    };

    struct ConstantBufferElement
    {
        ID3D11Buffer*   _constantBuffer;
        ConstantBuffer* _updateConstantBuffer;

        ConstantBufferElement()
            : _constantBuffer(nullptr)
            , _updateConstantBuffer(nullptr)
        {}
    };
}