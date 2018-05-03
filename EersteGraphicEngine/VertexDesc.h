#pragma once

#include "PrerequisitesCore.h"

namespace ege
{
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