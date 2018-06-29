#include "PointLight.h"
#include "LightModel.h"

#include "Time.h"
#include "Keyboard.h"

namespace ege
{
    const XMFLOAT3 PointLight::DefaultPosition = XMFLOAT3(-12.0f, 8.0f, 0.0f);
    const float    PointLight::DefaultRadius   = 5.0f;

    PointLight::PointLight()
        : Light(LightType::PointLight)
        , _radius(DefaultRadius)
    {
        GoTo(DefaultPosition);
        _position = DefaultPosition;

        _lightModel = ege_shared_ptr_new<LightModel>("point-light");
        _lightModel->Initialise();
        _lightModel->GoTo(_position);
        _lightModel->SetColor(Color(Colors::Yellow));
    }

    PointLight::~PointLight()
    {
    }

    void PointLight::Initialise()
    {
    }

    void PointLight::Update()
    {
        Light::Update();
        float deltaTime = gTime().GetFrameDelta();

        if (_lightModel != nullptr)
        {
            _lightModel->Update();
        }

        Rotate(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 2.5f * deltaTime, 0.0f));
    }

    void PointLight::Draw()
    {
        Light::Draw();

        if (_drawLightModel && _lightModel != nullptr)
        {
            _lightModel->Draw();
        }

        ID3D11DeviceContext* context = _renderAPI.GetDevice()->GetImmediateContext();
        SPtr<ConstantBufferElement> constantBuffer = _renderAPI.GetConstantBufferPtr(ConstantBufferType::LIGHT);
        LightConstantBuffer* constantBufferUpdate = (LightConstantBuffer*)&*constantBuffer->UpdateBuffer;

        UINT lightIndex = constantBufferUpdate->LightIndex;
        
        constantBufferUpdate->Lights[lightIndex].LightColor    = _color;
        constantBufferUpdate->Lights[lightIndex].LightPosition = _position;
        constantBufferUpdate->Lights[lightIndex].LightRadius   = _radius;
        constantBufferUpdate->Lights[lightIndex].LightType     = static_cast<UINT>(_type);

        constantBufferUpdate->LightIndex = lightIndex + 1;
    }

    void PointLight::DrawMetaData()
    {
        Light::DrawMetaData();

        if (_drawLightModel && _lightModel != nullptr)
        {
            _lightModel->DrawMetaData();
        }

        ID3D11DeviceContext* context = _renderAPI.GetDevice()->GetImmediateContext();
        SPtr<ConstantBufferElement> constantBuffer = _renderAPI.GetConstantBufferPtr(ConstantBufferType::LIGHT);
        LightConstantBuffer* constantBufferUpdate = (LightConstantBuffer*)&*constantBuffer->UpdateBuffer;

        UINT lightIndex = constantBufferUpdate->LightIndex;

        constantBufferUpdate->Lights[lightIndex].LightColor = _color;
        constantBufferUpdate->Lights[lightIndex].LightPosition = _position;
        constantBufferUpdate->Lights[lightIndex].LightRadius = _radius;
        constantBufferUpdate->Lights[lightIndex].LightType = static_cast<UINT>(_type);

        constantBufferUpdate->LightIndex = lightIndex + 1;
    }

    void PointLight::SetRadius(float radius)
    {
        _radius = radius;
    }

    const float& PointLight::GetRadius() const
    {
        return _radius;
    }
}