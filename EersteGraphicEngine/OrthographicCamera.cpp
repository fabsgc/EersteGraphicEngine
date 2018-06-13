#include "OrthographicCamera.h"

namespace ege
{
    const float OrthographicCamera::DefaultMinZoom = 0.001f;
    const float OrthographicCamera::DefaultMaxZoom = 128.0f;

    OrthographicCamera::OrthographicCamera()
        : Camera(CameraType::OrthographicCamera)
        , _zoom(0.01f)
        , _lastMousePosition(XMFLOAT2(1000.0f, 1000.0f))
    {
        _position = XMFLOAT3(0.0f, 1.0f, 0.0f);
    }

    OrthographicCamera::~OrthographicCamera()
    {
    }

    void OrthographicCamera::Update()
    {
        float deltaTime = _time.GetFrameDelta();

        if (_inputHandler.GetState("GO_LEFT").State == InputHandlerState::TRIGGERED)
            MoveX(-_translationSpeed * deltaTime * 3.0f);
        else if (_inputHandler.GetState("GO_RIGHT").State == InputHandlerState::TRIGGERED)
            MoveX(_translationSpeed * deltaTime * 3.0f);
        if (_inputHandler.GetState("GO_FORWARD").State == InputHandlerState::TRIGGERED)
            MoveY(_translationSpeed * deltaTime * 3.0f);
        else if (_inputHandler.GetState("GO_BACKWARD").State == InputHandlerState::TRIGGERED)
            MoveY(-_translationSpeed * deltaTime * 3.0f);

        MouseWheelState mouseWheelState = _mouse.GetWheelState();

        switch (mouseWheelState)
        {
        case MouseWheelState::ROLL_UP:
            Zoom(deltaTime * 0.05f);
            break;

        case MouseWheelState::ROLL_DOWN:
            Zoom(-deltaTime * 0.05f);
            break;
        }

        if (_mouse.GetState(MouseButtonName::LEFT) == MouseButtonState::TRIGGERED)
        {
            XMFLOAT2 mousePosition = _mouse.GetPosition();
            XMFLOAT2 mouseOldPosition = _mouse.GetOldPosition();

            if (mousePosition.x != _lastMousePosition.x || mousePosition.y != _lastMousePosition.y)
            {
                XMFLOAT2 distance = XMFLOAT2(mousePosition.x - mouseOldPosition.x, mousePosition.y - mouseOldPosition.y);
                MoveX(-distance.x * _zoom);
                MoveY(distance.y * _zoom);

                _lastMousePosition = mousePosition;
            }
        }

        if (_joypad.IsConnected())
        {
            float joypadRX = (float)_joypad.GetJoyStick(JoypadStickName::RIGHT).AxisX * 200.0f;
            float joypadRY = (float)_joypad.GetJoyStick(JoypadStickName::RIGHT).AxisY * 200.0f;

            float joypadLX = (float)_joypad.GetJoyStick(JoypadStickName::LEFT).AxisX;
            float joypadLY = (float)_joypad.GetJoyStick(JoypadStickName::LEFT).AxisY;

            if (abs(joypadLY) > 0.0f)
                MoveY(joypadLY * _translationSpeed * deltaTime * 3.0f);
            if (abs(joypadLX) > 0.0f)
                MoveX(joypadLX * _translationSpeed * deltaTime * 3.0f);
        }

        Camera::Update();
    }

    void OrthographicCamera::ComputeProjectionMatrix()
    {
        UINT windowWidth = gWindow().GetWindowWidth();
        UINT windowHeight = gWindow().GetWindowHeight();

        XMMATRIX Projection = XMMatrixOrthographicOffCenterLH(
            (((-(INT)windowWidth) / 2.0f) + _position.x) * _zoom,
            ((windowWidth / 2.0f) + _position.x) * _zoom,
            (((-(INT)windowHeight) / 2.0f) + _position.y) * _zoom,
            ((windowHeight / 2.0f) + _position.y) * _zoom,
            -512.0f + _position.y,
            512.0f + _position.y);

        XMVECTOR Right = XMVectorSet(_position.x + 1.0f, _position.y, 0.0f, 0.0f);
        XMVECTOR Up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
        XMVECTOR Look = XMVectorSet(_position.x, _position.y -0.67f, 1.0f, 0.0f);

        XMMATRIX View = XMMatrixLookAtLH(Right, Look, Up);

        XMStoreFloat4x4(&_projection, Projection);
        XMStoreFloat4x4(&_view, View);
    }

    void OrthographicCamera::Move(XMFLOAT3 distance)
    {
        if (distance.x != 0.0f)
        {
            _position.x += distance.x;
            _position.y += distance.x * 0.333333333f;
        }
        else
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
}