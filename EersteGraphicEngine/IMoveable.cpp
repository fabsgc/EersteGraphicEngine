#include "IMoveable.h"

namespace ege
{
    IMoveable::IMoveable()
    {
        XMStoreFloat4x4(&_world, XMMatrixIdentity());
        UpdateLocalPosition();
    }

    void IMoveable::UpdateLocalPosition()
    {
        XMFLOAT3 p = XMFLOAT3(0.0f, 0.0f, 0.0f);
        XMMATRIX worldInverse = XMMatrixInverse(nullptr, XMLoadFloat4x4(&_world));
        XMVECTOR position = XMVector3Transform(XMLoadFloat3(&p), XMLoadFloat4x4(&_world));
        XMStoreFloat3(&_position, position);
    }

    XMFLOAT3 IMoveable::GetPosition()
    {
        return _position;
    }

    XMFLOAT4X4 IMoveable::GetWorld()
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

    void IMoveable::GoTo(XMVECTOR position)
    {
        XMFLOAT3 P;
        XMStoreFloat3(&P, position);

        XMFLOAT3 movement = XMFLOAT3(
            P.x - _position.x,
            P.y - _position.y,
            P.z - _position.z
        );

        Move(movement);
    }

    void IMoveable::GoTo(XMFLOAT3 position)
    {
        GoTo(XMLoadFloat3(&position));
    }

    void IMoveable::GoTo(float x, float y, float z)
    {
        GoTo(XMFLOAT3(x, y, z));
    }

    void IMoveable::GoToX(float x)
    {
        GoTo(x, 0.0f, 0.0f);
    }

    void IMoveable::GoToY(float y)
    {
        GoTo(0.0f, y, 0.0f);
    }

    void IMoveable::GoToZ(float z)
    {
        GoTo(0.0f, 0.0f, z);
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

    void IMoveable::Rotate(XMVECTOR point, XMVECTOR eulerAngles)
    {
        XMFLOAT3 O = XMFLOAT3(0.0f, 0.0f, 0.0f);
        XMVECTOR origin = XMLoadFloat3(&O);

        XMMATRIX pointToOrigin = XMMatrixTranslationFromVector(origin - point);
        XMMATRIX originToPoint = XMMatrixTranslationFromVector(point - origin);

        XMMATRIX rotation0 = XMMatrixRotationQuaternion(XMQuaternionRotationRollPitchYawFromVector(eulerAngles));

        XMMATRIX rotation = pointToOrigin * rotation0 * originToPoint;

        XMMATRIX W = XMLoadFloat4x4(&_world);
        W *= rotation;
        XMStoreFloat4x4(&_world, W);

        UpdateLocalPosition();
    }

    void IMoveable::Rotate(XMVECTOR eulerAngles)
    {
        XMMATRIX W = XMLoadFloat4x4(&_world);
        XMMATRIX rotation = XMMatrixRotationQuaternion(XMQuaternionRotationRollPitchYawFromVector(eulerAngles));

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