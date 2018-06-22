#include "Light.h"
#include "LightModel.h"

namespace ege
{
    const XMFLOAT4 Light::DefaultLightColor = XMFLOAT4(1.0f, 1.0f, 1.0f, 0.2f);
    const bool Light::DefaultCastShadow     = true;
    const bool Light::DefaultDrawLightModel = false;
    const bool Light::DefaultIsEnabled      = true;

    Light::Light(LightType type)
        : IEntity(EntityType::Light)
        , _renderAPI(gRenderAPI())
        , _type(type)
        , _color(DefaultLightColor)
        , _drawLightModel(DefaultDrawLightModel)
        , _isEnabled(DefaultIsEnabled)
        , _castShadow(DefaultCastShadow)
    {
    }

    Light::~Light()
    {
    }

    void Light::Initialise()
    {
    }

    void Light::Update()
    {
    }

    void Light::Draw()
    {
    }

    void Light::Move(XMVECTOR movement)
    {
        IMoveable::Move(movement);

        if (_lightModel != nullptr)
        {
            _lightModel->Move(movement);
        }
    }

    void Light::Move(XMFLOAT3 movement)
    {
        Move(XMLoadFloat3(&movement));
    }

    void Light::Move(float x, float y, float z)
    {
        Move(XMFLOAT3(x, y, z));
    }

    void Light::Rotate(XMVECTOR point, XMVECTOR eulerAngles)
    {
        IMoveable::Rotate(point, eulerAngles);

        if (_lightModel != nullptr)
        {
            _lightModel->Rotate(point, eulerAngles);
        }
    }

    void Light::Rotate(XMVECTOR eulerAngles)
    {
        IMoveable::Rotate(eulerAngles);

        if (_lightModel != nullptr)
        {
            _lightModel->Rotate(eulerAngles);
        }
    }

    void Light::Rotate(XMFLOAT3 origin, XMFLOAT3 eulerAngles)
    {
        IMoveable::Rotate(origin, eulerAngles);
    }

    void Light::Rotate(XMFLOAT3 eulerAngles)
    {
        IMoveable::Rotate(eulerAngles);
    }

    void Light::Rotate(XMFLOAT3 origin, float roll, float pitch, float yaw)
    {
        IMoveable::Rotate(origin, roll, pitch, yaw);
    }

    void Light::Rotate(float roll, float pitch, float yaw)
    {
        IMoveable::Rotate(roll, pitch, yaw);
    }

    const LightType& Light::GetType() const
    {
        return _type;
    }

    const XMFLOAT4& Light::GetColor() const
    {
        return _color;
    }

    void Light::SetColor(XMFLOAT4 color)
    {
        _color = color;
    }

    void Light::SetColor(const Color color)
    {
        _color = color.ToXMFLOAT4();
    }

    void Light::SetDrawLightModel(bool drawLightModel)
    {
        _drawLightModel = drawLightModel;
    }

    void Light::SetCastShadow(bool castShadow)
    {
        _castShadow = castShadow;
    }

    void Light::SetEnabled(bool enabled)
    {
        _isEnabled = enabled;
    }

    const bool Light::GetCastShadow() const
    {
        return _castShadow;
    }

    const bool Light::IsEnabled() const
    {
        return _isEnabled;
    }
}