#include "PointLight.h"
#include "LightModel.h"

namespace ege
{
    const XMFLOAT3 PointLight::DefaultPosition = XMFLOAT3(-12.0f, 6.0f, -2.0f);
    const float    PointLight::DefaultRadius   = 5.0f;

    PointLight::PointLight()
        : Light(LightType::PointLight)
        , _radius(DefaultRadius)
    {
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
        _lightModel->Update();
    }

    void PointLight::Draw()
    {
        if (_drawLightModel)
        {
            _lightModel->Draw();
        }

        ID3D11DeviceContext* context = _renderAPI.GetDevice()->GetImmediateContext();
        ID3D11Buffer* constantBuffer = _renderAPI.GetConstantBuffer(ConstantBufferType::LIGHT);
        LightConstantBuffer* constantBufferUpdate = (LightConstantBuffer*)gRenderAPI().GetConstantBufferUpdate(ConstantBufferType::LIGHT);

        UINT lightIndex = constantBufferUpdate->LightIndex;
        
        constantBufferUpdate->Lights[lightIndex].LightColor    = _color;
        constantBufferUpdate->Lights[lightIndex].LightPosition = _position;
        constantBufferUpdate->Lights[lightIndex].LightRadius   = _radius;
        constantBufferUpdate->Lights[lightIndex].LightType     = static_cast<UINT>(_type);

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