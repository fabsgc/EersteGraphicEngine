#include "Light.h"

namespace ege
{
    Light::Light(LightType type)
        : IEntity(EntityType::Light)
        , _type(type)
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

    LightType Light::GetType()
    {
        return _type;
    }
}