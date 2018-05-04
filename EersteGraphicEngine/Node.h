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

        void          Initialise();
        void          InsertNode(String name, SPtr<Node> node);
        void          InsertEntity(String name, SPtr<IEntity> entity);
        void          Update() override;
        void          Draw() override;

        SPtr<Scene>   GetScene();
        SPtr<Node>    GetParent();
        SPtr<IEntity> GetEntity(String name);
        void          SetScene(SPtr<Scene> scene);
        void          SetParent(SPtr<Node> parent);

    private:
        SPtr<Scene>                _scene;
        SPtr<Node>                 _parent;
        Map<String, SPtr<Node>>    _child;
        Map<String, SPtr<IEntity>> _entities;
    };
}