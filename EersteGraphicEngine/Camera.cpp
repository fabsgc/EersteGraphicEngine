#include "Camera.h"
#include "Window.h"

namespace ege
{
    const float Camera::DefaultNearZ            = 0.001f;
    const float Camera::DefaultFarZ             = 2048.0f;
    const float Camera::DefaultTranslationSpeed = 10.0f;
    const float Camera::DefaultRotationSpeed    = 5.0f;

    Camera::Camera()
        : Camera(CameraType::GenericCamera)
    {
    }

    Camera::Camera(CameraType type)
        : Node(NodeType::Camera)
        , _cameraType(type)
        , _renderAPI(gRenderAPI())
        , _inputHandler(gInputHandler())
        , _keyboard(gKeyboard())
        , _joypad(gJoypad())
        , _mouse(gMouse())
        , _time(gTime())
        , _nearZ(DefaultNearZ)
        , _farZ(DefaultFarZ)
        , _translationSpeed(DefaultTranslationSpeed)
        , _rotationSpeed(DefaultTranslationSpeed)
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
        Node::Update();

        if (_needUpdate)
        {
            ComputeProjectionMatrix();
            _needUpdate = false;
        }
    }

    void Camera::Draw()
    {
        Node::Draw();

        SPtr<ConstantBufferElement> constantBuffer = _renderAPI.GetConstantBufferPtr(ConstantBufferType::FRAME);
        FrameConstantBuffer* constantBufferUpdate = (FrameConstantBuffer*)&*constantBuffer->UpdateBuffer;
        ID3D11DeviceContext* context = _renderAPI.GetDevice()->GetImmediateContext();

        XMMATRIX view = XMLoadFloat4x4(&_view);
        XMMATRIX projection = XMLoadFloat4x4(&_projection);

        constantBufferUpdate->View = XMMatrixTranspose(view);
        constantBufferUpdate->Projection = XMMatrixTranspose(projection);
        constantBufferUpdate->CameraPosition = _position;
    }

    void Camera::DrawMetaData()
    {
        Node::Draw();

        SPtr<ConstantBufferElement> constantBuffer = _renderAPI.GetConstantBufferPtr(ConstantBufferType::FRAME);
        FrameConstantBuffer* constantBufferUpdate = (FrameConstantBuffer*)&*constantBuffer->UpdateBuffer;
        ID3D11DeviceContext* context = _renderAPI.GetDevice()->GetImmediateContext();

        XMMATRIX view = XMLoadFloat4x4(&_view);
        XMMATRIX projection = XMLoadFloat4x4(&_projection);

        constantBufferUpdate->View = XMMatrixTranspose(view);
        constantBufferUpdate->Projection = XMMatrixTranspose(projection);
        constantBufferUpdate->CameraPosition = _position;
    }

    const CameraType& Camera::GetType() const
    {
        return _cameraType;
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

    const float& Camera::GetTranslationSpeed() const
    {
        return _translationSpeed;
    }

    const float& Camera::GetRotationSpeed() const
    {
        return _rotationSpeed;
    }

    const float& Camera::GetNearZ() const
    {
        return _nearZ;
    }

    const float& Camera::GetFarZ() const
    {
        return _farZ;
    }

    void Camera::SetNearZ(float nearZ)
    {
        _nearZ = nearZ;
    }

    void Camera::SetFarZ(float farZ)
    {
        _farZ = farZ;
    }
    void Camera::SetTranslationSpeed(float translationSpeed)
    {
        _translationSpeed = translationSpeed;
    }

    void Camera::SetRotationSpeed(float rotationSpeed)
    {
        _rotationSpeed = rotationSpeed;
    }

    void Camera::Move(XMVECTOR movement)
    {
        Node::Move(movement);
    }
    
    void Camera::MoveStrafe(XMVECTOR movement)
    {
        Node::MoveStrafe(movement);
    }
    
    void Camera::Scale(XMVECTOR origin, XMVECTOR scale)
    {
        Node::Scale(origin, scale);
    }
    
    void Camera::Scale(XMVECTOR scale)
    {
        Node::Scale(scale);
    }
    
    void Camera::Rotate(XMVECTOR origin, XMVECTOR eulerAngles)
    {
        Node::Rotate(origin, eulerAngles);
    }
    
    void Camera::Rotate(XMVECTOR eulerAngles)
    {
        Node::Rotate(eulerAngles);
    }
}