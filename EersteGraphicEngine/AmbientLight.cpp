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
        Light::Update();
    }

    void AmbientLight::Draw()
    {
        Light::Draw();

        ID3D11DeviceContext* context = _renderAPI.GetDevice()->GetImmediateContext();
        SPtr<ConstantBufferElement> constantBuffer = _renderAPI.GetConstantBufferPtr(ConstantBufferType::LIGHT);
        LightConstantBuffer* constantBufferUpdate = (LightConstantBuffer*)&*constantBuffer->UpdateBuffer;

        constantBufferUpdate->AmbientColor = _color;
    }

    void AmbientLight::DrawMetaData()
    {
        Draw();
    }
}