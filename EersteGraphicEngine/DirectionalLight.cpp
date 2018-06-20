#include "DirectionalLight.h"

namespace ege
{
    const XMFLOAT3 DirectionalLight::DefaultDirection = XMFLOAT3(0.5f, -0.5f, 0.5f);

    DirectionalLight::DirectionalLight()
        : Light(LightType::DirectionalLight)
        , _direction(DefaultDirection)
    {
        _lightModel = ege_shared_ptr_new<LightModel>("directional-light");
        _lightModel->Initialise();

        _lightModel->GoTo(20.0f, 20.0f, 20.0f);
    }

    DirectionalLight::~DirectionalLight()
    {
    }

    void DirectionalLight::Initialise()
    {
    }

    void DirectionalLight::Update()
    {
        _lightModel->Update();
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

        constantBufferUpdate->LightColor     = _color;
        constantBufferUpdate->LightDirection = _direction;
        constantBufferUpdate->LightType      = static_cast<UINT>(_type);
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