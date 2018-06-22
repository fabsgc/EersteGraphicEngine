#include "SpotLight.h"
#include "LightModel.h"

#include "Time.h"
#include "Keyboard.h"

namespace ege
{
    const XMFLOAT3 SpotLight::DefaultPosition   = XMFLOAT3(-2.0f, 3.0f, -2.0f);
    const XMFLOAT3 SpotLight::DefaultDirection  = XMFLOAT3(0.0f, -1.0f, 0.0f);
    const float    SpotLight::DefaultRadius     = 5.0f;
    const float    SpotLight::DefaultInnerAngle = 0.5f;
    const float    SpotLight::DefaultOuterAngle = 0.1f;

    SpotLight::SpotLight()
        : Light(LightType::SpotLight)
        , _direction(DefaultDirection)
        , _radius(DefaultRadius)
        , _innerAngle(DefaultInnerAngle)
        , _outerAngle(DefaultOuterAngle)
    {
        GoTo(DefaultPosition);
        _position    = DefaultPosition;

        _lightModel  = ege_shared_ptr_new<LightModel>("spot-light");
        _lightModel->Initialise();
        _lightModel->GoTo(_position);
        _lightModel->SetColor(Color(Colors::Yellow));
    }

    SpotLight::~SpotLight()
    {
    }

    void SpotLight::Initialise()
    {
    }

    void SpotLight::Update()
    {
        float deltaTime = gTime().GetFrameDelta();
        Light::Update();

        if (_lightModel != nullptr)
        {
            _lightModel->Update();
        }

        Rotate(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 2.5f * deltaTime, 0.0f));
    }

    void SpotLight::Draw()
    {
        if (_drawLightModel)
        {
            _lightModel->Draw();
        }

        ID3D11DeviceContext* context = _renderAPI.GetDevice()->GetImmediateContext();
        ID3D11Buffer* constantBuffer = _renderAPI.GetConstantBuffer(ConstantBufferType::LIGHT);
        LightConstantBuffer* constantBufferUpdate = (LightConstantBuffer*)gRenderAPI().GetConstantBufferUpdate(ConstantBufferType::LIGHT);

        UINT lightIndex = constantBufferUpdate->LightIndex;

        constantBufferUpdate->Lights[lightIndex].LightColor = _color;
        constantBufferUpdate->Lights[lightIndex].LightDirection  = _direction;
        constantBufferUpdate->Lights[lightIndex].LightPosition   = _position;
        constantBufferUpdate->Lights[lightIndex].LightRadius     = _radius;
        constantBufferUpdate->Lights[lightIndex].LightInnerAngle = _innerAngle;
        constantBufferUpdate->Lights[lightIndex].LightOuterAngle = _outerAngle;
        constantBufferUpdate->Lights[lightIndex].LightType       = static_cast<UINT>(_type);

        
        constantBufferUpdate->LightIndex = lightIndex + 1;
    }

    const XMFLOAT3& SpotLight::GetDirection() const
    {
        return _direction;
    }

    void SpotLight::SetDirection(XMFLOAT3 direction)
    {
        _direction = direction;
    }

    void SpotLight::SetRadius(float radius)
    {
        _radius = radius;
    }

    const float& SpotLight::GetRadius() const
    {
        return _radius;
    }

    void SpotLight::SetInnerAngle(float innerAngle)
    {
        _innerAngle = innerAngle;
    }

    const float& SpotLight::GetInnerAngle() const
    {
        return _innerAngle;
    }

    void SpotLight::SetOuterAngle(float outerAngle)
    {
        _outerAngle = outerAngle;
    }

    const float& SpotLight::GetOuterAngle() const
    {
        return _outerAngle;
    }

    void SpotLight::Rotate(XMVECTOR point, XMVECTOR eulerAngles)
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

    void SpotLight::Rotate(XMVECTOR eulerAngles)
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

    void SpotLight::Rotate(XMFLOAT3 origin, XMFLOAT3 eulerAngles)
    {
        Light::Rotate(origin, eulerAngles);
    }

    void SpotLight::Rotate(XMFLOAT3 eulerAngles)
    {
        Light::Rotate(eulerAngles);
    }

    void SpotLight::Rotate(XMFLOAT3 origin, float roll, float pitch, float yaw)
    {
        Light::Rotate(origin, roll, pitch, yaw);
    }

    void SpotLight::Rotate(float roll, float pitch, float yaw)
    {
        Light::Rotate(roll, pitch, yaw);
    }
}