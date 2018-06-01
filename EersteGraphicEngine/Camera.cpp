#include "Camera.h"
#include "Window.h"

namespace ege
{
    const float Camera::DefaultFov = XM_PIDIV4;
    const float Camera::DefaultNearZ = 0.01f;
    const float Camera::DefaultFarZ = 100.0f;
    const float Camera::DefaultTranslationSpeed = 4.0f;
    const float Camera::DefaultRotationSpeed = 0.4f;

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