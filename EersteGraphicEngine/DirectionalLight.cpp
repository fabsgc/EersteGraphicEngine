#include "DirectionalLight.h"
#include "LightModel.h"

#include "Time.h"
#include "Keyboard.h"

namespace ege
{
    const XMFLOAT3 DirectionalLight::DefaultPosition  = XMFLOAT3(20.0f, 20.0f, 20.0f);
    const XMFLOAT3 DirectionalLight::DefaultDirection = XMFLOAT3(0.5f, -0.5f, 0.5f);

    DirectionalLight::DirectionalLight()
        : Light(LightType::DirectionalLight)
        , _direction(DefaultDirection)
    {
        GoTo(DefaultPosition);
        _position = DefaultPosition;

        _lightModel = ege_shared_ptr_new<LightModel>("directional-light");
        _lightModel->Initialise();
        _lightModel->GoTo(_position);
        _lightModel->SetColor(Color(Colors::Yellow));
    }

    DirectionalLight::~DirectionalLight()
    {
    }

    void DirectionalLight::Initialise()
    {
    }

    void DirectionalLight::Update()
    {
        float deltaTime = gTime().GetFrameDelta();
        Light::Update();

        if (_lightModel != nullptr)
        {
            _lightModel->Update();
        }

        Rotate(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 2.5f * deltaTime, 0.0f));
    }

    void DirectionalLight::Draw()
    {
        if (_drawLightModel)
        {
            _lightModel->Draw();
        }

        ID3D11DeviceContext* context = _renderAPI.GetDevice()->GetImmediateContext();
        ID3D11Buffer* constantBuffer = _renderAPI.GetConstantBuffer(ConstantBufferType::LIGHT);
        LightConstantBuffer* constantBufferUpdate = (LightConstantBuffer*)gRenderAPI().GetConstantBufferUpdate(ConstantBufferType::LIGHT);

        UINT lightIndex = constantBufferUpdate->LightIndex;

        constantBufferUpdate->Lights[lightIndex].LightColor     = _color;
        constantBufferUpdate->Lights[lightIndex].LightDirection = _direction;
        constantBufferUpdate->Lights[lightIndex].LightType      = static_cast<UINT>(_type);

        constantBufferUpdate->LightIndex = lightIndex + 1;
    }

    const XMFLOAT3& DirectionalLight::GetDirection() const
    {
        return _direction;
    }

    void DirectionalLight::SetDirection(XMFLOAT3 direction)
    {
        _direction = direction;
    }

    void DirectionalLight::Rotate(XMVECTOR point, XMVECTOR eulerAngles)
    {
        XMFLOAT3 O = XMFLOAT3(0.0f, 0.0f, 0.0f);
        XMVECTOR origin = XMLoadFloat3(&O);
        XMMATRIX pointToOrigin = XMMatrixTranslationFromVector(origin - point);
        XMMATRIX originToPoint = XMMatrixTranslationFromVector(point - origin);
        XMMATRIX rotation0 = XMMatrixRotationQuaternion(XMQuaternionRotationRollPitchYawFromVector(eulerAngles));
        XMMATRIX rotation = pointToOrigin * rotation0 * originToPoint;
        XMMATRIX W = XMLoadFloat4x4(&_world);
        W *= rotation;
        XMStoreFloat4x4(&_world, W);

        XMVECTOR look = XMVector3TransformCoord(XMLoadFloat3(&_direction), rotation);
        XMStoreFloat3(&_direction, look);

        UpdateLocalPosition();

        if (_lightModel != nullptr)
        {
            _lightModel->Rotate(point, eulerAngles);
        }
    }

    void DirectionalLight::Rotate(XMVECTOR eulerAngles)
    {
        XMMATRIX W = XMLoadFloat4x4(&_world);
        XMMATRIX rotation = XMMatrixRotationQuaternion(XMQuaternionRotationRollPitchYawFromVector(eulerAngles));

        W = rotation * W;
        XMStoreFloat4x4(&_world, W);

        XMVECTOR look = XMVector3TransformCoord(XMLoadFloat3(&_direction), rotation);
        XMStoreFloat3(&_direction, look);

        UpdateLocalPosition();

        if (_lightModel != nullptr)
        {
            _lightModel->Rotate(eulerAngles);
        }
    }

    void DirectionalLight::Rotate(XMFLOAT3 origin, XMFLOAT3 eulerAngles)
    {
        Light::Rotate(origin, eulerAngles);
    }

    void DirectionalLight::Rotate(XMFLOAT3 eulerAngles)
    {
        Light::Rotate(eulerAngles);
    }

    void DirectionalLight::Rotate(XMFLOAT3 origin, float roll, float pitch, float yaw)
    {
        Light::Rotate(origin, roll, pitch, yaw);
    }

    void DirectionalLight::Rotate(float roll, float pitch, float yaw)
    {
        Light::Rotate(roll, pitch, yaw);
    }
}