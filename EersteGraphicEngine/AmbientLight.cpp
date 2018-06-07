#include "AmbientLight.h"
#include "Keyboard.h"

namespace ege
{
    AmbientLight::AmbientLight()
        : Light(LightType::AmbientLight)
    {
    }

    AmbientLight::~AmbientLight()
    {
    }

    void AmbientLight::Initialise()
    {
    }

    void AmbientLight::Update()
    {
    }

    void AmbientLight::Draw()
    {
        ID3D11DeviceContext* context = _renderAPI.GetDevice()->GetImmediateContext();
        ID3D11Buffer* constantBuffer = _renderAPI.GetConstantBuffer(ConstantBufferType::LIGHT);
        LightConstantBuffer* constantBufferUpdate = (LightConstantBuffer*)gRenderAPI().GetConstantBufferUpdate(ConstantBufferType::LIGHT);

        constantBufferUpdate->AmbientColor = _color;
    }
}