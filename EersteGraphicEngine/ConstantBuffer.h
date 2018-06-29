#pragma once

#include "PrerequisitesCore.h"

namespace ege
{
    struct LightDesc
    {
        XMFLOAT4 LightColor;
        XMFLOAT3 LightDirection;
        /* PADDING */ float    Padding1;
        XMFLOAT3 LightPosition;
        float    LightRadius;
        float    LightInnerAngle;
        float    LightOuterAngle;
        UINT     LightType;
        /* PADDING */ float    Padding2;

        LightDesc()
            : LightColor(XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f))
            , LightDirection(XMFLOAT3(1.0f, 1.0f, 1.0f))
            , LightPosition(XMFLOAT3(1.0f, 1.0f, 1.0f))
            , LightRadius(5.0f)
            , LightInnerAngle(0.5f)
            , LightOuterAngle(0.1f)
            , LightType(0)
        {}
    };

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

    struct QuadConstantBuffer : public ConstantBuffer
    {
        XMMATRIX View;
        XMMATRIX Projection;
        XMMATRIX World;

        QuadConstantBuffer()
            : View(XMMatrixIdentity())
            , Projection(XMMatrixIdentity())
            , World(XMMatrixIdentity())
        {}
    };

    struct ConstantBufferElement
    {
        ID3D11Buffer*   Buffer;
        SPtr<ConstantBuffer> UpdateBuffer;

        ConstantBufferElement()
            : Buffer(nullptr)
            , UpdateBuffer(nullptr)
        {}
    };
}