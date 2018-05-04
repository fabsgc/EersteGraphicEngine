#pragma once

#include "PrerequisitesCore.h"
#include "IEntity.h"
#include "Shader.h"

namespace ege
{
    enum class LightType
    {
        PointLight,
        SportLight,
        DirectionalLight
    };

    class Light: public IEntity
    {
    public:
        Light(LightType type);
        virtual ~Light() = 0;

        virtual void Initialise() = 0;
        virtual void Update() = 0;
        virtual void Draw() = 0;

        LightType    GetType();

    protected:
        LightType _type;
    };
}