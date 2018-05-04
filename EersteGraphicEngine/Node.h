#pragma once

#include "PrerequisitesCore.h"
#include "IUpdatable.h"
#include "IDrawable.h"
#include "IMoveable.h"
#include "IEntity.h"

namespace ege
{
    class Node : public IUpdatable, public IDrawable, public IMoveable
    {
    public:
        Node();
        ~Node();

        void     Initialise();
        void     Update() override;
        void     Draw() override;

    private:
        SPtr<Node>            _parent;
        Vector<SPtr<Node>>    _child;
        Vector<SPtr<IEntity>> _entities;
    };
}