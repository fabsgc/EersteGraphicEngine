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
            entity.second->Draw();
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
}