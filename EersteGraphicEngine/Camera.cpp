#include "Camera.h"
#include "Window.h"

namespace ege
{
    const float Camera::DefaultFov = XM_PIDIV4;
    const float Camera::DefaultNearZ = 0.01f;
    const float Camera::DefaultFarZ = 1000.0f;
    const float Camera::DefaultTranslationSpeed = 4.0f;
    const float Camera::DefaultRotationSpeed = 0.25f;

    Camera::Camera()
        : Camera(CameraType::Genereic)
    {
    }

    Camera::Camera(CameraType type)
        : IEntity(EntityType::Camera)
        , _cameraType(type)
        , _renderAPI(gRenderAPI())
        , _inputHandler(gInputHandler())
        , _keyboard(gKeyboard())
        , _joypad(gJoypad())
        , _mouse(gMouse())
        , _time(gTime())
        , _fov(DefaultFov)
        , _nearZ(DefaultNearZ)
        , _farZ(DefaultFarZ)
        , _translationSpeed(DefaultTranslationSpeed)
        , _rotationSpeed(DefaultRotationSpeed)
        , _position(XMFLOAT3(0.0f, 1.0f, -10.0f))
        , _right(XMFLOAT3(1.0f, 0.0f, 0.0f))
        , _up(XMFLOAT3(0.0f, 1.0f, 0.0f))
        , _look(XMFLOAT3(0.0f, 0.0f, 1.0f))
        , _needUpdate(false)
    {
        Initialise();
    }

    Camera::~Camera()
    {
    }

    void Camera::Initialise()
    {
        ComputeProjectionMatrix();
    }

    void Camera::Update()
    {
        _frustum.Build(*this);

        if (_needUpdate)
        {
            ComputeProjectionMatrix();
            _needUpdate = false;
        }
    }

    void Camera::Draw()
    {
        FrameConstantBuffer* constantBufferUpdate = (FrameConstantBuffer*)gRenderAPI().GetConstantBufferUpdate(ConstantBufferType::FRAME);
        ID3D11Buffer* constantBuffer = _renderAPI.GetConstantBuffer(ConstantBufferType::FRAME);
        ID3D11DeviceContext* context = _renderAPI.GetDevice()->GetImmediateContext();

        XMMATRIX view = XMLoadFloat4x4(&_view);
        XMMATRIX projection = XMLoadFloat4x4(&_projection);

        constantBufferUpdate->View = XMMatrixTranspose(view);
        constantBufferUpdate->Projection = XMMatrixTranspose(projection);
        constantBufferUpdate->CameraPosition = _position;
    }

    void Camera::ComputeProjectionMatrix()
    {
    }

    const CameraType& Camera::GetType() const
    {
        return _cameraType;
    }

    void Camera::Pitch(float angle)
    {
    }

    void Camera::Roll(float angle)
    {
    }

    void Camera::Yaw(float angle)
    {
    }

    const XMFLOAT4X4& Camera::GetView() const
    {
        return _view;
    }

    const XMFLOAT4X4& Camera::GetProjection() const
    {
        return _projection;
    }

    const XMFLOAT3& Camera::GetPosition() const
    {
        return _position;
    }

    const XMFLOAT3& Camera::GetRight() const
    {
        return _right;
    }

    const XMFLOAT3& Camera::GetLook() const
    {
        return _look;
    }

    const XMFLOAT3& Camera::GetUp() const
    {
        return _up;
    }

    const float& Camera::GetFov() const
    {
        return _fov;
    }

    const float& Camera::GetNearZ() const
    {
        return _nearZ;
    }

    const float& Camera::GetFarZ() const
    {
        return _farZ;
    }

    const float& Camera::GetRotationSpeed() const
    {
        return _rotationSpeed;
    }

    const float& Camera::GetTranslationSpeed() const
    {
        return _translationSpeed;
    }
}