#pragma once

#include "PrerequisitesCore.h"
#include "RenderAPI.h"
#include "IEntity.h"
#include "Frustum.h"

namespace ege
{
    class Camera: public IEntity
    {
    public:
        Camera();
        ~Camera();

        void              Initialise() override;
        void              Update() override;
        void              Draw() override;
        void              ComputeProjectionMatrix();

        const XMFLOAT4X4& GetView() const;
        const XMFLOAT4X4& GetProjection() const;
        const XMFLOAT3&   GetPosition() const;
        const XMFLOAT3&   GetRight() const;
        const XMFLOAT3&   GetLook() const;
        const XMFLOAT3&   GetUp() const;
        const float&      GetFov() const;
        const float&      GetNearZ() const;
        const float&      GetFarZ() const;
        const float&      GetRotationSpeed() const;
        const float&      GetTranslationSpeed() const;

    public:
        static const float DefaultFov;
        static const float DefaultNearZ;
        static const float DefaultFarZ;
        static const float DefaultTranslationSpeed;
        static const float DefaultRotationSpeed;

    protected:
        RenderAPI&         _renderAPI;

        XMFLOAT4X4         _view;
        XMFLOAT4X4         _projection;

        XMFLOAT3           _position;
        XMFLOAT3           _right;
        XMFLOAT3           _look;
        XMFLOAT3           _up;

        float              _fov;
        float              _nearZ;
        float              _farZ;
        float              _rotationSpeed;
        float              _translationSpeed;

        Frustum            _frustum;
    };
}