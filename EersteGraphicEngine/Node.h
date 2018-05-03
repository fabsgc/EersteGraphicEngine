#pragma once

#include "PrerequisitesCore.h"
#include "IUpdatable.h"
#include "IDrawable.h"
#include "IEntity.h"
#include "Model.h"

namespace ege
{
    class Node: public IEntity
    {
    public:
        Node() {};
        ~Node() {};

        void Initialise() override;
        void Update() override;
        void Draw() override;

    private:
        SPtr<Node>          _parent;
        Vector<SPtr<Node>>  _child;
        Vector<SPtr<Model>> _models;
    };
}