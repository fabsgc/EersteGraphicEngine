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

    void Node::DeleteNode(String name)
    {
        _child.erase(name);
    }

    void Node::DeleteNode(SPtr<Node> node)
    {
        for (auto it = _child.begin(); it != _child.end(); it++)
        {
            if (it->second == node)
            {
                _child.erase(it);
                break;
            }
        }
    }

    void Node::DeleteEntity(String name)
    {
        _entities.erase(name);
    }

    void Node::DeleteEntity(SPtr<IEntity> entity)
    {
        for (auto it = _entities.begin(); it != _entities.end(); it++)
        {
            if (it->second == entity)
            {
                _entities.erase(it);
                break;
            }
        }
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

    void Node::UpdateLocalPosition()
    {
        XMMATRIX worldInverse = XMMatrixInverse(nullptr, XMLoadFloat4x4(&_world));
        XMVECTOR position = XMVector3Transform(XMLoadFloat3(&_position), XMLoadFloat4x4(&_world));
        XMStoreFloat3(&_position, position);
    }

    void Node::Move(XMVECTOR movement)
    {
        for (auto child : _child)
        {
            child.second->Move(movement);
        }

        for (auto entity : _entities)
        {
            switch (entity.second->GetType())
            {
            case EntityType::Light:
                entity.second->Move(movement);
                break;

            case EntityType::Model:
                entity.second->Move(movement);
                break;
            }
        }
    }

    void Node::Scale(XMVECTOR origin, XMVECTOR scale)
    {
        for (auto child : _child)
        {
            child.second->Scale(origin, scale);
        }

        for (auto entity : _entities)
        {
            switch (entity.second->GetType())
            {
            case EntityType::Light:
                entity.second->Scale(origin, scale);
                break;

            case EntityType::Model:
                entity.second->Scale(origin, scale);
                break;
            }
        }
    }

    void Node::Scale(XMVECTOR scale)
    {
        XMFLOAT3 position = GetPosition();
        XMVECTOR P = XMLoadFloat3(&position);

        for (auto child : _child)
        {
            child.second->Scale(P, scale);
        }

        for (auto entity : _entities)
        {
            switch (entity.second->GetType())
            {
            case EntityType::Light:
                entity.second->Scale(P, scale);
                break;

            case EntityType::Model:
                entity.second->Scale(P, scale);
                break;
            }
        }
    }

    void Node::Rotate(XMVECTOR origin, XMVECTOR eulerAngles)
    {
        for (auto child : _child)
        {
            child.second->Rotate(origin, eulerAngles);
        }

        for (auto entity : _entities)
        {
            switch (entity.second->GetType())
            {
            case EntityType::Light:
                entity.second->Rotate(origin, eulerAngles);
                break;

            case EntityType::Model:
                entity.second->Rotate(origin, eulerAngles);
                break;
            }
        }
    }

    void Node::Rotate(XMVECTOR eulerAngles)
    {
        XMFLOAT3 position = GetPosition();
        XMVECTOR P = XMLoadFloat3(&position);

        for (auto child : _child)
        {
            child.second->Rotate(P, eulerAngles);
        }

        for (auto entity : _entities)
        {
            switch (entity.second->GetType())
            {
            case EntityType::Light:
                entity.second->Rotate(P, eulerAngles);
                break;

            case EntityType::Model:
                entity.second->Rotate(P, eulerAngles);
                break;
            }
        }
    }
}