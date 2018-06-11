#include "DirectionalLight.h"

namespace ege
{
    const XMFLOAT3 DirectionalLight::DefaultDirection = XMFLOAT3(0.5f, -0.5f, 0.5f);

    DirectionalLight::DirectionalLight()
        : Light(LightType::DirectionalLight)
        , _direction(DefaultDirection)
    {
        _lightSchema = ege_shared_ptr_new<LightSchema>("directional-light");
    }

    DirectionalLight::~DirectionalLight()
    {
    }

    void DirectionalLight::Initialise()
    {
    }

    void DirectionalLight::Update()
    {
        _lightSchema->Update();
    }

    void DirectionalLight::Draw()
    {
        _lightSchema->Draw();

        ID3D11DeviceContext* context = _renderAPI.GetDevice()->GetImmediateContext();
        ID3D11Buffer* constantBuffer = _renderAPI.GetConstantBuffer(ConstantBufferType::LIGHT);
        LightConstantBuffer* constantBufferUpdate = (LightConstantBuffer*)gRenderAPI().GetConstantBufferUpdate(ConstantBufferType::LIGHT);

        constantBufferUpdate->LightColor     = _color;
        constantBufferUpdate->LightDirection = _direction;
        constantBufferUpdate->LightType      = (float)_type;
    }

    const XMFLOAT3& DirectionalLight::GetDirection() const
    {
        return _direction;
    }

    void DirectionalLight::SetDirection(XMFLOAT3 direction)
    {
        _direction = direction;
    }
}