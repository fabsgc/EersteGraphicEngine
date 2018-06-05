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
        ID3D11Buffer* constantBuffer = _renderAPI.GetConstantBuffer();
        ConstantBuffer* constantBufferUpdate = _renderAPI.GetConstantBufferUpdate();

        constantBufferUpdate->AmbientColor = _color;
    }
}