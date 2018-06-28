#pragma once

#include "PrerequisitesCore.h"

namespace ege
{
    enum class VertexType
    {
        FULL  = 0,
        SHORT = 1
    };

    static Vector<D3D11_INPUT_ELEMENT_DESC> VertexElementShortDesc =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
    };

    static Vector<D3D11_INPUT_ELEMENT_DESC> VertexElementDesc =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "TANGENT", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "BINORMAL", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
    };

    struct VertexShortDesc
    {
        XMFLOAT3 Position;
        XMFLOAT2 Texture;

        VertexShortDesc()
            : Position(XMFLOAT3(0.0f, 0.0f, 0.0f))
            , Texture(XMFLOAT2(0.0f, 0.0f))
        {}

        VertexShortDesc(XMFLOAT3 position, XMFLOAT2 texture)
            : Position(position)
            , Texture(texture)
        {}
    };

    struct VertexDesc
    {
        XMFLOAT3 Position;
        XMFLOAT4 Color;
        XMFLOAT2 Texture;
        XMFLOAT3 Normal;
        XMFLOAT3 Tangent;
        XMFLOAT3 BiNormal;

        VertexDesc()
        {}

        VertexDesc(XMFLOAT3 position, XMFLOAT4 color)
            : Position(position)
            , Color(color)
            , Texture(XMFLOAT2(0.0f, 0.0f))
            , Normal(position)
            , Tangent(position)
            , BiNormal(position)
        {}

        VertexDesc(XMFLOAT3 position, XMFLOAT4 color, XMFLOAT3 normal)
            : Position(position)
            , Color(color)
            , Texture(XMFLOAT2(0.0f, 0.0f))
            , Normal(normal)
            , Tangent(position)
            , BiNormal(position)
        {}

        VertexDesc(XMFLOAT3 position, XMFLOAT4 color, XMFLOAT3 normal, XMFLOAT3 tangent, XMFLOAT3 biNormal)
            : Position(position)
            , Color(color)
            , Texture(XMFLOAT2(0.0f, 0.0f))
            , Normal(normal)
            , Tangent(tangent)
            , BiNormal(biNormal)
        {}
    };
}