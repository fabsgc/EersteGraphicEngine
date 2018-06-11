#pragma once

#include "PrerequisitesCore.h"
#include "IUpdatable.h"
#include "IDrawable.h"
#include "IMoveable.h"

namespace ege
{
    enum class EntityType
    {
        Model,
        Light,
        Camera,
        Generic
    };

    class IEntity: public IUpdatable, public IDrawable, public IMoveable
    {
    public:
        IEntity(EntityType type) : _type(type) {};
        virtual ~IEntity() {};
        virtual void Initialise() = 0;
        virtual void Draw() = 0;
        virtual void Update() = 0;

        EntityType GetType()
        {
            return _type;
        }

    protected:
        EntityType _type;
    };
}