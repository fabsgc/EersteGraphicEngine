#include "OrthographicCamera.h"

namespace ege
{
    const float OrthographicCamera::DefaultMinZoom   = 0.01f;
    const float OrthographicCamera::DefaultMaxZoom   = 256.0f;

    OrthographicCamera::OrthographicCamera()
        : Camera(CameraType::OrthographicCamera)
        , _zoom(0.5f)
        , _lastMousePosition(XMFLOAT2(1000.0f, 1000.0f))
    {
        _zoomSpeed = 1.0f;
        _position = XMFLOAT3(0.0f, 0.0f, 0.0f);
        ComputeProjectionMatrix();
    }

    OrthographicCamera::OrthographicCamera(CameraType type)
        : Camera(type)
        , _zoom(0.5f)
        , _lastMousePosition(XMFLOAT2(1000.0f, 1000.0f))
    {
        _zoomSpeed = 1.0f;
        _position = XMFLOAT3(0.0f, 0.0f, 0.0f);
        ComputeProjectionMatrix();
    }

    OrthographicCamera::~OrthographicCamera()
    {
    }

    void OrthographicCamera::Update()
    {
        float deltaTime       = _time.GetFrameDelta();
        float speedModulation = (_zoom) > 1.0f ? 2.0f : 0.5f;

        XMFLOAT2 movement = XMFLOAT2(0.0f, 0.0f);
        float zoom        = 0.0f;

        if (_inputHandler.GetState("GO_LEFT").State == InputHandlerState::TRIGGERED)
            movement.x = -_translationSpeed;
        else if (_inputHandler.GetState("GO_RIGHT").State == InputHandlerState::TRIGGERED)
            movement.x = _translationSpeed;

        if (_inputHandler.GetState("GO_FORWARD").State == InputHandlerState::TRIGGERED)
            movement.y = _translationSpeed;
        else if (_inputHandler.GetState("GO_BACKWARD").State == InputHandlerState::TRIGGERED)
            movement.y = -_translationSpeed;

        MouseWheelState mouseWheelState = _mouse.GetWheelState();

        switch (mouseWheelState)
        {
        case MouseWheelState::ROLL_UP:
            zoom = _zoomSpeed;
            break;

        case MouseWheelState::ROLL_DOWN:
            zoom = -_zoomSpeed;
            break;
        }

        if (_mouse.GetState(MouseButtonName::LEFT) == MouseButtonState::TRIGGERED)
        {
            XMFLOAT2 mousePosition = _mouse.GetPosition();
            XMFLOAT2 mouseOldPosition = _mouse.GetOldPosition();

            if (mousePosition.x != _lastMousePosition.x || mousePosition.y != _lastMousePosition.y)
            {
                XMFLOAT2 distance = XMFLOAT2(mousePosition.x - mouseOldPosition.x, mousePosition.y - mouseOldPosition.y);
                
                movement.x = -distance.x;
                movement.y = distance.y;

                _lastMousePosition = mousePosition;
            }
        }

        if (_joypad.IsConnected())
        {
            float joypadRX = (float)_joypad.GetJoyStick(JoypadStickName::RIGHT).AxisX * 200.0f;
            float joypadRY = (float)_joypad.GetJoyStick(JoypadStickName::RIGHT).AxisY * 200.0f;

            float joypadLX = (float)_joypad.GetJoyStick(JoypadStickName::LEFT).AxisX;
            float joypadLY = (float)_joypad.GetJoyStick(JoypadStickName::LEFT).AxisY;

            if (fabs(joypadLX) > 0.0f)
                movement.x = -joypadLX;
            if (fabs(joypadLY) > 0.0f)
                movement.y = -joypadLY;
        }

        if (fabs(movement.x) > 0.0f)
            Strafe(movement.x * _translationSpeed * deltaTime * speedModulation, 0.0f, 0.0f);
        if(fabs(movement.y) > 0.0f)
            Strafe(0.0f, movement.y * _translationSpeed * deltaTime * speedModulation, 0.0f);

        if (fabs(zoom) > 0.0f)
            Zoom(zoom * deltaTime);

        Camera::Update();
    }

    void OrthographicCamera::ComputeProjectionMatrix()
    {
        UINT windowWidth = gWindow().GetWindowWidth();
        UINT windowHeight = gWindow().GetWindowHeight();

        XMMATRIX Projection = XMMatrixOrthographicOffCenterLH(
            (((-(INT)windowWidth) / 2.0f) + _position.x - 1.0f) * _zoom,
            ((windowWidth / 2.0f) + _position.x - 1.0f) * _zoom,
            (((-(INT)windowHeight) / 2.0f) + _position.y) * _zoom,
            ((windowHeight / 2.0f) + _position.y) * _zoom,
            -512.0f + _position.y,
            512.0f + _position.y);

        XMVECTOR Right = XMVectorSet(_position.x, _position.y, 0.0f, 0.0f);
        XMVECTOR Up    = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
        XMVECTOR Look = XMVectorSet(_position.x, _position.y - 0.67f, 1.0f, 0.0f);

        XMMATRIX View = XMMatrixLookAtLH(Right, Look, Up);

        XMStoreFloat4x4(&_projection, Projection);
        XMStoreFloat4x4(&_view, View);
    }

    void OrthographicCamera::Strafe(float x, float y, float z)
    {
        Strafe(XMFLOAT3(x, y, z));
    }

    void OrthographicCamera::Strafe(XMFLOAT3 distance)
    {
        if (distance.x != 0.0f)
        {
            _position.x += distance.x;
        }
        
        if(distance.y != 0.0f)
        {
            _position.y += distance.y;
        }
        
        _position.z += distance.z;
        _needUpdate = true;
    }

    void OrthographicCamera::Zoom(float zoom)
    {
        _zoom -= zoom;
        _zoom = MathUtility::Clamp(_zoom, DefaultMinZoom, DefaultMaxZoom);

        _needUpdate = true;
    }

    void OrthographicCamera::SetPosition(XMFLOAT3 position)
    {
        _position = position;
        _needUpdate = true;
    }

    void OrthographicCamera::SetZoom(float zoom)
    {
        _zoom -= zoom;
        _zoom = MathUtility::Clamp(_zoom, DefaultMinZoom, DefaultMaxZoom);

        _needUpdate = true;
    }
}