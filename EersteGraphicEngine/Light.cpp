#include "Light.h"
#include "LightModel.h"

namespace ege
{
    const XMFLOAT4 Light::DefaultLightColor = XMFLOAT4(1.0f, 1.0f, 1.0f, 0.2f);
    const bool Light::DefaultCastShadow     = true;
    const bool Light::DefaultDrawLightModel = false;
    const bool Light::DefaultIsEnabled      = true;

    Light::Light(LightType type)
        : Node(NodeType::Light)
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
        Node::Update();
    }

    void Light::Draw()
    {
        Node::Draw();
    }

    void Light::Move(XMVECTOR movement)
    {
        Node::Move(movement);

        if (_lightModel != nullptr)
        {
            _lightModel->Move(movement);
        }
    }

    void Light::MoveStrafe(XMVECTOR movement)
    {
        Node::MoveStrafe(movement);

        if (_lightModel != nullptr)
        {
            _lightModel->MoveStrafe(movement);
        }
    }

    void Light::Rotate(XMVECTOR point, XMVECTOR eulerAngles)
    {
        Node::Rotate(point, eulerAngles);

        if (_lightModel != nullptr)
        {
            _lightModel->Rotate(point, eulerAngles);
        }
    }

    void Light::Scale(XMVECTOR origin, XMVECTOR scale)
    {
        Node::Scale(origin, scale);
    }

    void Light::Scale(XMVECTOR scale)
    {
        Node::Scale(scale);
    }

    void Light::Rotate(XMVECTOR eulerAngles)
    {
        Node::Rotate(eulerAngles);

        if (_lightModel != nullptr)
        {
            _lightModel->Rotate(eulerAngles);
        }
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