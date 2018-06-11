#include "PointLight.h"

namespace ege
{
    const XMFLOAT3 PointLight::DefaultPosition = XMFLOAT3(-2.0f, 2.0f, -2.0f);
    const float    PointLight::DefaultRadius   = 5.0f;

    PointLight::PointLight()
        : Light(LightType::PointLight)
        , _radius(DefaultRadius)
    {
        _position = DefaultPosition;
        _lightSchema = ege_shared_ptr_new<LightSchema>("point-light");
    }

    PointLight::~PointLight()
    {
    }

    void PointLight::Initialise()
    {
    }

    void PointLight::Update()
    {
        _lightSchema->Update();
    }

    void PointLight::Draw()
    {
        _lightSchema->Draw();

        ID3D11DeviceContext* context = _renderAPI.GetDevice()->GetImmediateContext();
        ID3D11Buffer* constantBuffer = _renderAPI.GetConstantBuffer(ConstantBufferType::LIGHT);
        LightConstantBuffer* constantBufferUpdate = (LightConstantBuffer*)gRenderAPI().GetConstantBufferUpdate(ConstantBufferType::LIGHT);

        constantBufferUpdate->LightColor     = _color;
        constantBufferUpdate->LightPosition  = _position;
        constantBufferUpdate->LightType      = (float)_type;
    }
}