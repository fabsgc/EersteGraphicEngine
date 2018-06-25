#include "OrthographicCamera.h"

namespace ege
{
    const float OrthographicCamera::DefaultMinZoom = 0.001f;
    const float OrthographicCamera::DefaultMaxZoom = 256.0f;

    OrthographicCamera::OrthographicCamera()
        : Camera(CameraType::OrthographicCamera)
        , _zoom(0.5f)
        , _lastMousePosition(XMFLOAT2(1000.0f, 1000.0f))
    {
        _position = XMFLOAT3(0.0f, 1.0f, 0.0f);
    }

    OrthographicCamera::~OrthographicCamera()
    {
    }

    void OrthographicCamera::Update()
    {
        /*float deltaTime = _time.GetFrameDelta();
        float speedModulation = (10 * _zoom) > 2.0f ? 10 * _zoom : 2.0f;

        if (_inputHandler.GetState("GO_LEFT").State == InputHandlerState::TRIGGERED)
            MoveX(-_translationSpeed * deltaTime * speedModulation);
        else if (_inputHandler.GetState("GO_RIGHT").State == InputHandlerState::TRIGGERED)
            MoveX(_translationSpeed * deltaTime * speedModulation);
        if (_inputHandler.GetState("GO_FORWARD").State == InputHandlerState::TRIGGERED)
            MoveY(_translationSpeed * deltaTime * speedModulation);
        else if (_inputHandler.GetState("GO_BACKWARD").State == InputHandlerState::TRIGGERED)
            MoveY(-_translationSpeed * deltaTime * speedModulation);

        MouseWheelState mouseWheelState = _mouse.GetWheelState();

        switch (mouseWheelState)
        {
        case MouseWheelState::ROLL_UP:
            Zoom(deltaTime * speedModulation);
            break;

        case MouseWheelState::ROLL_DOWN:
            Zoom(-deltaTime * speedModulation);
            break;
        }

        if (_mouse.GetState(MouseButtonName::LEFT) == MouseButtonState::TRIGGERED)
        {
            XMFLOAT2 mousePosition = _mouse.GetPosition();
            XMFLOAT2 mouseOldPosition = _mouse.GetOldPosition();

            if (mousePosition.x != _lastMousePosition.x || mousePosition.y != _lastMousePosition.y)
            {
                XMFLOAT2 distance = XMFLOAT2(mousePosition.x - mouseOldPosition.x, mousePosition.y - mouseOldPosition.y);
                MoveX(-distance.x * _translationSpeed * deltaTime * 0.75f);
                MoveY(distance.y * _translationSpeed * deltaTime * 0.75f);

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
                MoveY(- joypadLY * _translationSpeed * deltaTime * speedModulation * 3.0f);
            if (abs(joypadLX) > 0.0f)
                MoveX(- joypadLX * _translationSpeed * deltaTime * speedModulation * 3.0f);
        }*/

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

        XMVECTOR Right = XMVectorSet(_position.x, _position.y, 0.0f, 0.0f);
        XMVECTOR Up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
        XMVECTOR Look = XMVectorSet(_position.x, _position.y -1.0f, 1.0f, 0.0f);

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

    void OrthographicCamera::SetPosition(XMFLOAT3 position)
    {
        _position = position;
        _needUpdate = true;
    }

    void OrthographicCamera::Move(XMVECTOR movement)
    {}

    void OrthographicCamera::Rotate(XMVECTOR origin, XMVECTOR eulerAngles)
    {}

    void OrthographicCamera::Rotate(XMVECTOR eulerAngles)
    {}
}