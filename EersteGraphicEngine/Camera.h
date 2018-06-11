#pragma once

#include "PrerequisitesCore.h"
#include "InputHandler.h"
#include "RenderAPI.h"
#include "IEntity.h"
#include "Frustum.h"
#include "Joypad.h"
#include "Mouse.h"
#include "Time.h"

namespace ege
{
    enum class CameraType
    {
        FirstPerson,
        FlyingCamera,
        ThirdPerson,
        Genereic
    };

    class Camera: public IEntity
    {
    public:
        Camera();
        Camera(CameraType type);
        ~Camera();

        void              Initialise() override;
        void              Update() override;
        void              Draw() override;
        virtual void      ComputeProjectionMatrix();

        const CameraType& GetType() const;

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

        virtual void      Pitch(float angle);
        virtual void      Roll(float angle);
        virtual void      Yaw(float angle);

        virtual void      UpdateLocalPosition() override {};
        virtual void      Move(XMVECTOR movement) override {};
        virtual void      Scale(XMVECTOR origin, XMVECTOR scale) override {};
        virtual void      Scale(XMVECTOR scale) override {};
        virtual void      Rotate(XMVECTOR origin, XMVECTOR eulerAngles) override {};
        virtual void      Rotate(XMVECTOR eulerAngles) override {};

    public:
        static const float DefaultFov;
        static const float DefaultNearZ;
        static const float DefaultFarZ;
        static const float DefaultTranslationSpeed;
        static const float DefaultRotationSpeed;

    protected:
        CameraType         _cameraType;

        RenderAPI&         _renderAPI;
        InputHandler&      _inputHandler;
        Keyboard&          _keyboard;
        Joypad&            _joypad;
        Mouse&             _mouse;
        Time&              _time;

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

        bool               _needUpdate;
    };
}