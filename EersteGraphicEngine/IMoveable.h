#pragma once

#include "PrerequisitesCore.h"

namespace ege
{
    class IMoveable
    {
    public:
        IMoveable() {}
        virtual ~IMoveable() = 0 {}

        void UpdateLocalPosition()
        {
            XMMATRIX worldInverse = XMMatrixInverse(nullptr, XMLoadFloat4x4(&_world));
            XMVECTOR position = XMVector3Transform(XMLoadFloat3(&_position), XMLoadFloat4x4(&_world));
            XMStoreFloat3(&_position, position);
        }

    protected:
        XMFLOAT4X4 _world;
        XMFLOAT3   _position;
    };
}