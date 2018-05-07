#include "Node.h"

namespace ege
{
    Node::Node()
        : _scene(nullptr)
        , _parent(nullptr)
    {
    }
    
    Node::~Node()
    {
    }

    void Node::Initialise()
    {
    }

    void Node::InsertNode(String name, SPtr<Node> node)
    {
        _child.insert(Pair<String, SPtr<Node>>(name, std::move(node)));
    }

    void Node::InsertEntity(String name, SPtr<IEntity> entity)
    {
        _entities.insert(Pair<String, SPtr<IEntity>>(name, std::move(entity)));
    }

    void Node::Update()
    {
        for (auto child : _child)
        {
            child.second->Update();
        }

        for (auto entity : _entities)
        {
            entity.second->Update();
        }
    }

    void Node::Draw()
    {
        for (auto child : _child)
        {
            child.second->Draw();
        }

        for (auto entity : _entities)
        {
            if (entity.second->GetType() != EntityType::Camera)
            {
                entity.second->Draw();
            }
        }
    }

    SPtr<Scene> Node::GetScene()
    {
        return _scene;
    }

    SPtr<Node> Node::GetParent()
    {
        return _parent;
    }

    SPtr<IEntity> Node::GetEntity(String name)
    {
        auto found = _entities.find(name);
        EGE_ASSERT_ERROR((found != _entities.end()), ("Entity " + name + " not found"));

        return found->second;
    }

    void Node::SetScene(SPtr<Scene> scene)
    {
        _scene = scene;
    }

    void Node::SetParent(SPtr<Node> parent)
    {
        _parent = parent;
    }
}