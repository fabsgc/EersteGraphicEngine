#pragma once

#include "PrerequisitesCore.h"

namespace ege
{
    class IMoveable
    {
    public:
        IMoveable();
        virtual ~IMoveable() = 0 {}
        virtual void UpdateLocalPosition();

        virtual XMFLOAT3   GetPosition();
        virtual XMFLOAT4X4 GetWorld();

        virtual void Move(XMVECTOR movement);
        virtual void Move(XMFLOAT3 movement);
        virtual void Move(float x = 0.0f, float y = 0.0f, float z = 0.0f);
        virtual void MoveX(float x = 0.0f);
        virtual void MoveY(float y = 0.0f);
        virtual void MoveZ(float z = 0.0f);

        virtual void GoTo(XMVECTOR position);
        virtual void GoTo(XMFLOAT3 position);
        virtual void GoTo(float x, float y, float z);
        virtual void GoToX(float x);
        virtual void GoToY(float y);
        virtual void GoToZ(float z);

        virtual void Scale(XMVECTOR origin, XMVECTOR scale);
        virtual void Scale(XMVECTOR scale);
        virtual void Scale(XMFLOAT3 origin, XMFLOAT3 scale);
        virtual void Scale(XMFLOAT3 scale);
        virtual void Scale(XMFLOAT3 origin, float x, float y, float z);
        virtual void Scale(float x, float y, float z);
        virtual void ScaleX(XMFLOAT3 origin, float x);
        virtual void ScaleX(float x);
        virtual void ScaleY(XMFLOAT3 origin, float y);
        virtual void ScaleY(float y);
        virtual void ScaleZ(XMFLOAT3 origin, float z);
        virtual void ScaleZ(float z);

        virtual void Rotate(XMVECTOR origin, XMVECTOR eulerAngles);
        virtual void Rotate(XMVECTOR eulerAngles);
        virtual void Rotate(XMFLOAT3 origin, XMFLOAT3 eulerAngles);
        virtual void Rotate(XMFLOAT3 eulerAngles);
        virtual void Rotate(XMFLOAT3 origin, float yaw, float pitch, float roll);
        virtual void Rotate(float yaw, float pitch, float roll);
        virtual void RotateYaw(XMFLOAT3 origin, float yaw);
        virtual void RotateYaw(float yaw);
        virtual void RotatePitch(XMFLOAT3 origin, float pitch);
        virtual void RotatePitch(float pitch);
        virtual void RotateRoll(XMFLOAT3 origin, float roll);
        virtual void RotateRoll(float roll);

    protected:
        XMFLOAT3   _position;
        XMFLOAT4X4 _world;
    };
}