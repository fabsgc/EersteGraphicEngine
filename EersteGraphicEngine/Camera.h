#pragma once

#include "PrerequisitesCore.h"
#include "InputHandler.h"
#include "RenderAPI.h"
#include "IEntity.h"
#include "Joypad.h"
#include "Mouse.h"
#include "Time.h"

namespace ege
{
    enum class CameraType
    {
        FlyingCamera,
        FirstPersonCamera,
        ThirdPersonCamera,
        OrthographicCamera,
        GenericCamera
    };

    class Camera: public IEntity
    {
    public:
        Camera();
        Camera(CameraType type);
        virtual ~Camera();

        void              Initialise() override;
        void              Update() override;
        void              Draw() override;
        virtual void      ComputeProjectionMatrix() {};

        const CameraType& GetType() const;
        const XMFLOAT4X4& GetView() const;
        const XMFLOAT4X4& GetProjection() const;
        const float&      GetNearZ() const;
        const float&      GetFarZ() const;

        const XMFLOAT3&   GetPosition() const;
        const float&      GetTranslationSpeed() const;

        virtual void      UpdateLocalPosition() override {};
        virtual void      Move(XMVECTOR movement) override {};
        virtual void      Scale(XMVECTOR origin, XMVECTOR scale) override {};
        virtual void      Scale(XMVECTOR scale) override {};
        virtual void      Rotate(XMVECTOR origin, XMVECTOR eulerAngles) override {};
        virtual void      Rotate(XMVECTOR eulerAngles) override {};

    public:
        static const float DefaultNearZ;
        static const float DefaultFarZ;
        static const float DefaultTranslationSpeed;

    protected:
        RenderAPI&         _renderAPI;
        InputHandler&      _inputHandler;
        Keyboard&          _keyboard;
        Joypad&            _joypad;
        Mouse&             _mouse;
        Time&              _time;

        CameraType         _cameraType;
        XMFLOAT4X4         _view;
        XMFLOAT4X4         _projection;
        XMFLOAT3           _position;
        XMFLOAT3           _right;
        XMFLOAT3           _look;
        XMFLOAT3           _up;

        float              _nearZ;
        float              _farZ;
        float              _translationSpeed;

        bool               _needUpdate;
    };
}