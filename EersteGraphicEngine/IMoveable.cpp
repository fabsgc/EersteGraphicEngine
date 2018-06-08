#include "IMoveable.h"

namespace ege
{
    XMFLOAT3 IMoveable::GetPosition()
    {
        return _position;
    }

    XMFLOAT4X4 IMoveable::GetWrodl()
    {
        return _world;
    }

    void IMoveable::Move(XMVECTOR movement)
    {
        XMMATRIX W = XMLoadFloat4x4(&_world);
        W *= XMMatrixTranslationFromVector(movement);
        XMStoreFloat4x4(&_world, W);

        UpdateLocalPosition();
    }

    void IMoveable::Move(XMFLOAT3 movement)
    {
        Move(XMLoadFloat3(&movement));
    }

    void IMoveable::Move(float x, float y, float z)
    {
        Move(XMFLOAT3(x, y , z));
    }

    void IMoveable::MoveX(float x)
    {
        Move(x, 0.0f, 0.0f);
    }

    void IMoveable::MoveY(float y)
    {
        Move(0.0f, y, 0.0f);
    }

    void IMoveable::MoveZ(float z)
    {
        Move(0.0f, 0.0f, z);
    }

    void IMoveable::Scale(XMVECTOR origin, XMVECTOR scale)
    {
        XMFLOAT3 C = XMFLOAT3(0.0f, 0.0f, 0.0f);
        XMVECTOR center = XMLoadFloat3(&C);
        XMVECTOR distance = origin - center;

        Move(-distance);

        XMMATRIX W = XMLoadFloat4x4(&_world);
        W *= XMMatrixScalingFromVector(scale);
        XMStoreFloat4x4(&_world, W);

        Move(distance);

        UpdateLocalPosition();
    }

    void IMoveable::Scale(XMVECTOR scale)
    {
        XMMATRIX W = XMLoadFloat4x4(&_world);
        W = XMMatrixScalingFromVector(scale) * W;
        XMStoreFloat4x4(&_world, W);

        UpdateLocalPosition();
    }

    void IMoveable::Scale(XMFLOAT3 origin, XMFLOAT3 scale)
    {
        Scale(XMLoadFloat3(&origin), XMLoadFloat3(&scale));
    }

    void IMoveable::Scale(XMFLOAT3 scale)
    {
        Scale(XMLoadFloat3(&scale));
    }

    void IMoveable::Scale(XMFLOAT3 origin, float x, float y, float z)
    {
        Scale(origin, XMFLOAT3(x, y, z));
    }

    void IMoveable::Scale(float x, float y, float z)
    {
        Scale(XMFLOAT3(x, y, z));
    }

    void IMoveable::ScaleX(XMFLOAT3 origin, float x)
    {
        Scale(origin, x, 0.0f, 0.0f);
    }

    void IMoveable::ScaleX(float x)
    {
        Scale(x, 0.0f, 0.0f);
    }

    void IMoveable::ScaleY(XMFLOAT3 origin, float y)
    {
        Scale(origin, 0.0f, y, 0.0f);
    }

    void IMoveable::ScaleY(float y)
    {
        Scale(0.0f, y, 0.0f);
    }

    void IMoveable::ScaleZ(XMFLOAT3 origin, float z)
    {
        Scale(origin, 0.0f, 0.0f, z);
    }

    void IMoveable::ScaleZ(float z)
    {
        Scale(0.0f, 0.0f, z);
    }

    void IMoveable::Rotate(XMVECTOR origin, XMVECTOR eulerAngles)
    {
        /*XMFLOAT3 C = XMFLOAT3(0.0f, 0.0f, 0.0f);
        XMFLOAT3 P = GetPosition();
        XMVECTOR position = XMLoadFloat3(&P);
        XMVECTOR center = XMLoadFloat3(&C);
        XMVECTOR distance = origin - position;
        XMVECTOR ddd = position - center;

        Move(-distance);
        Move(-ddd);

        XMMATRIX W = XMLoadFloat4x4(&_world);
        XMVECTOR quaternion = XMQuaternionRotationRollPitchYawFromVector(eulerAngles);
        XMMATRIX rotation = XMMatrixRotationQuaternion(quaternion);

        W = rotation * W;
        XMStoreFloat4x4(&_world, W);
        
        Move(distance);

        UpdateLocalPosition();*/

        XMFLOAT3 P = GetPosition();
        XMVECTOR position = XMLoadFloat3(&P);
        XMVECTOR distance = origin - position;

        XMMATRIX W = XMLoadFloat4x4(&_world);
        XMVECTOR quaternion = XMQuaternionRotationRollPitchYawFromVector(eulerAngles);
        XMMATRIX rotation = XMMatrixRotationQuaternion(quaternion);

        W = rotation * W;
        XMStoreFloat4x4(&_world, W);

        Move(distance);

        UpdateLocalPosition();
    }

    void IMoveable::Rotate(XMVECTOR eulerAngles)
    {
        XMMATRIX W = XMLoadFloat4x4(&_world);
        XMVECTOR quaternion = XMQuaternionRotationRollPitchYawFromVector(eulerAngles);
        XMMATRIX rotation = XMMatrixRotationQuaternion(quaternion);

        W = rotation * W;
        XMStoreFloat4x4(&_world, W);

        UpdateLocalPosition();
    }

    void IMoveable::Rotate(XMFLOAT3 origin, XMFLOAT3 eulerAngles)
    {
        Rotate(XMLoadFloat3(&origin), XMLoadFloat3(&eulerAngles));
    }

    void IMoveable::Rotate(XMFLOAT3 eulerAngles)
    {
        Rotate(XMLoadFloat3(&eulerAngles));
    }

    void IMoveable::Rotate(XMFLOAT3 origin, float roll, float pitch, float yaw)
    {
        Rotate(origin, XMFLOAT3(roll, pitch, yaw));
    }

    void IMoveable::Rotate(float roll, float pitch, float yaw)
    {
        Rotate(XMFLOAT3(roll, pitch, yaw));
    }

    void IMoveable::RotateYaw(XMFLOAT3 origin, float yaw)
    {
        Rotate(origin, 0.0f, 0.0f, yaw);
    }

    void IMoveable::RotateYaw(float yaw)
    {
        Rotate(0.0f, 0.0f, yaw);
    }

    void IMoveable::RotatePitch(XMFLOAT3 origin, float pitch)
    {
        Rotate(origin, 0.0f, pitch, 0.0f);
    }

    void IMoveable::RotatePitch(float pitch)
    {
        Rotate(0.0f, pitch, 0.0f);
    }

    void IMoveable::RotateRoll(XMFLOAT3 origin, float roll)
    {
        Rotate(origin, roll, 0.0f, 0.0f);
    }

    void IMoveable::RotateRoll(float roll)
    {
        Rotate(roll, 0.0f, 0.0f);
    }
}