#pragma once

#include "PrerequisitesCore.h"
#include "IMoveable.h"
#include "IUpdatable.h"
#include "IDrawable.h"

namespace ege
{
    enum class NodeType
    {
        Node   = 1,
        Model  = 2,
        Light  = 3,
        Camera = 4
    };

    class Node : public IUpdatable, public IDrawable, public IMoveable
    {
    public:
        Node(NodeType type = NodeType::Node);
        ~Node();

        virtual void  Initialise();
        void          InsertNode(String name, SPtr<Node> node);
        void          DeleteNode(String name);
        void          DeleteNode(SPtr<Node> node);
        void          Update() override;
        void          Draw() override;
        virtual void  DrawMetaData();

        NodeType      GetType();
        SPtr<Scene>   GetScene();
        SPtr<Node>    GetParent();
        void          SetScene(SPtr<Scene> scene);
        void          SetParent(SPtr<Node> parent);

        using         IMoveable::Move;
        using         IMoveable::Scale;
        using         IMoveable::Rotate;
        virtual void  Move(XMVECTOR movement) override;
        virtual void  MoveStrafe(XMVECTOR movement) override;
        virtual void  Scale(XMVECTOR origin, XMVECTOR scale) override;
        virtual void  Scale(XMVECTOR scale) override;
        virtual void  Rotate(XMVECTOR origin, XMVECTOR eulerAngles) override;
        virtual void  Rotate(XMVECTOR eulerAngles) override;

    protected:
        SPtr<Scene>                _scene;
        SPtr<Node>                 _parent;
        Map<String, SPtr<Node>>    _child;

        NodeType                   _type;
    };
}