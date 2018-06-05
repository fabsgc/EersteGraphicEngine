#include "Camera.h"
#include "Window.h"

namespace ege
{
    const float Camera::DefaultFov = XM_PIDIV4;
    const float Camera::DefaultNearZ = 0.01f;
    const float Camera::DefaultFarZ = 100.0f;
    const float Camera::DefaultTranslationSpeed = 4.0f;
    const float Camera::DefaultRotationSpeed = 0.25f;

    Camera::Camera()
        : IEntity(EntityType::Camera)
        , _renderAPI(gRenderAPI())
        , _fov(DefaultFov)
        , _nearZ(DefaultNearZ)
        , _farZ(DefaultFarZ)
        , _translationSpeed(DefaultTranslationSpeed)
        , _rotationSpeed(DefaultRotationSpeed)
    {
        Initialise();
    }

    Camera::~Camera()
    {
    }

    void Camera::Initialise()
    {
        _position = XMFLOAT3(0.0f, 2.0f, -6.0f);
        _right = XMFLOAT3(1.0f, 0.0f, 0.0f);
        _look = XMFLOAT3(0.0f, -0.5f, 1.5f);
        _up = XMFLOAT3(0.0f, 1.0f, 0.0f);

        ComputeProjectionMatrix();
    }

    void Camera::Update()
    {
        _frustum.Build(*this);
    }

    void Camera::Draw()
    {
        ConstantBuffer* constantBufferUpdate = _renderAPI.GetConstantBufferUpdate();
        ID3D11Buffer* constantBuffer = _renderAPI.GetConstantBuffer();
        ID3D11DeviceContext* context = _renderAPI.GetDevice()->GetImmediateContext();

        XMMATRIX view = XMLoadFloat4x4(&_view);
        XMMATRIX projection = XMLoadFloat4x4(&_projection);

        constantBufferUpdate->View = XMMatrixTranspose(view);
        constantBufferUpdate->Projection = XMMatrixTranspose(projection);
        constantBufferUpdate->CameraPosition = XMFLOAT4(_position.x, _position.y, _position.z, 0.0f);

        context->UpdateSubresource(constantBuffer, 0, nullptr, constantBufferUpdate, 0, 0);
    }

    void Camera::ComputeProjectionMatrix()
    {
        UINT windowWidth = gWindow().GetWindowWidth();;
        UINT windowHeight = gWindow().GetWindowHeight();

        XMVECTOR R = XMLoadFloat3(&_right);
        XMVECTOR U = XMLoadFloat3(&_up);
        XMVECTOR L = XMLoadFloat3(&_look);
        XMVECTOR P = XMLoadFloat3(&_position);

        // Keep camera's axes orthogonal to each other and of unit length.
        L = XMVector3Normalize(L);
        U = XMVector3Normalize(XMVector3Cross(L, R));

        // U, L already ortho-normal, so no need to normalize cross product.
        R = XMVector3Cross(U, L);

        // Fill in the view matrix entries.
        float x = -XMVectorGetX(XMVector3Dot(P, R));
        float y = -XMVectorGetX(XMVector3Dot(P, U));
        float z = -XMVectorGetX(XMVector3Dot(P, L));

        XMStoreFloat3(&_right, R);
        XMStoreFloat3(&_up, U);
        XMStoreFloat3(&_look, L);

        _view(0, 0) = _right.x;
        _view(1, 0) = _right.y;
        _view(2, 0) = _right.z;
        _view(3, 0) = x;

        _view(0, 1) = _up.x;
        _view(1, 1) = _up.y;
        _view(2, 1) = _up.z;
        _view(3, 1) = y;

        _view(0, 2) = _look.x;
        _view(1, 2) = _look.y;
        _view(2, 2) = _look.z;
        _view(3, 2) = z;

        _view(0, 3) = 0.0f;
        _view(1, 3) = 0.0f;
        _view(2, 3) = 0.0f;
        _view(3, 3) = 1.0f;

        XMStoreFloat4x4(&_projection, XMMatrixPerspectiveFovLH(_fov, windowWidth / (FLOAT)windowHeight, _nearZ, _farZ));
    }

    void Camera::Move(XMFLOAT3 distance)
    {
        XMVECTOR right = XMLoadFloat3(&_right);
        XMVECTOR look = XMLoadFloat3(&_look);
        XMVECTOR up = XMLoadFloat3(&_up);
        XMVECTOR position = XMLoadFloat3(&_position);
        XMVECTOR movement = XMLoadFloat3(&distance);

        XMVECTOR strafe = right * XMVectorGetX(movement);
        position += strafe;

        XMVECTOR forward = look * XMVectorGetY(movement);
        position += forward;

        XMVECTOR climb = up * XMVectorGetZ(movement);
        position += climb;

        XMStoreFloat3(&_position, position);

        ComputeProjectionMatrix();
    }
    
    void Camera::Move(float x, float y, float z)
    {
        Move(XMFLOAT3(x, y, z));
    }

    void Camera::MoveX(float x)
    {
        Move(x, 0.0f, 0.0f);
    }

    void Camera::MoveY(float y)
    {
        Move(0.0f, y, 0.0f);
    }

    void Camera::MoveZ(float z)
    {
        Move(0.0f, 0.0f, z);
    }

    void Camera:: RotateFrom(XMFLOAT3 angle, XMFLOAT3 position)
    {
        ComputeProjectionMatrix();
    }

    void Camera::RotateFrom(float x, float y, float z, XMFLOAT3 position)
    {
        RotateFrom(XMFLOAT3(x, y, z), position);
    }

    void Camera::RotateX(float x, XMFLOAT3 position)
    {
        RotateFrom(x, 0.0f, 0.0f, position);
    }

    void Camera::RotateY(float y, XMFLOAT3 position)
    {
        RotateFrom(0.0f, y, 0.0f, position);
    }

    void Camera::RotateZ(float z, XMFLOAT3 position)
    {
        RotateFrom(0.0f, 0.0f, z, position);
    }

    void Camera::Rotate(XMFLOAT3 angle)
    {
        RotateFrom(angle, _position);
    }

    void Camera::Rotate(float x, float y, float z)
    {
        Rotate(XMFLOAT3(x, y, z));
    }

    void Camera::RotateX(float x)
    {
        Rotate(x, 0.0f, 0.0f);
    }

    void Camera::RotateY(float y)
    {
        Rotate(0.0f, y, 0.0f);
    }

    void Camera::RotateZ(float z)
    {
        Rotate(0.0f, 0.0f, z);
    }

    void Camera::Pitch(float angle)
    {
        XMMATRIX T = XMMatrixRotationAxis(XMLoadFloat3(&_right), angle);

		XMVECTOR up = XMVector3TransformCoord(XMLoadFloat3(&_up), T);
		XMVECTOR look = XMVector3TransformCoord(XMLoadFloat3(&_look), T);

		XMStoreFloat3(&_up, up);
		XMStoreFloat3(&_look, look);

        ComputeProjectionMatrix();
    }

    void Camera::Roll(float angle)
    {
        XMMATRIX T = XMMatrixRotationAxis(XMLoadFloat3(&_look), angle);

        XMVECTOR right = XMVector3TransformCoord(XMLoadFloat3(&_right), T);
        XMVECTOR up = XMVector3TransformCoord(XMLoadFloat3(&_up), T);

        XMStoreFloat3(&_right, right);
        XMStoreFloat3(&_up, up);

        ComputeProjectionMatrix();
    }

    void Camera::Yaw(float angle)
    {
        XMMATRIX T = XMMatrixRotationY(angle);

        XMVECTOR right = XMVector3TransformCoord(XMLoadFloat3(&_right), T);
        XMVECTOR look = XMVector3TransformCoord(XMLoadFloat3(&_look), T);

        XMStoreFloat3(&_right, right);
        XMStoreFloat3(&_look, look);

        ComputeProjectionMatrix();
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