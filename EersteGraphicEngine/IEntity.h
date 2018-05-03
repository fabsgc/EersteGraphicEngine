#pragma once

#include "PrerequisitesCore.h"
#include "IUpdatable.h"
#include "IDrawable.h"
#include "IMoveable.h"

namespace ege
{
    class IEntity: public IUpdatable, public IDrawable, public IMoveable
    {
    public:
        IEntity() {};
        virtual ~IEntity() = 0;
        virtual void Initialise() = 0;
        virtual void Draw() = 0;
        virtual void Update() = 0;
    };
}