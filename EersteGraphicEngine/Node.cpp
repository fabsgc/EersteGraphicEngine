#include "Node.h"

namespace ege
{
    Node::Node(NodeType nodeType)
        : _scene(nullptr)
        , _parent(nullptr)
        , _type(nodeType)
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
        _children.insert(Pair<String, SPtr<Node>>(name, std::move(node)));
    }

    void Node::DeleteNode(String name)
    {
        _children.erase(name);
    }

    void Node::DeleteNode(SPtr<Node> node)
    {
        for (auto it = _children.begin(); it != _children.end(); it++)
        {
            if (it->second == node)
            {
                _children.erase(it);
                break;
            }
        }
    }

    void Node::Update()
    {
        for (auto child : _children)
        {
            child.second->Update();
        }
    }

    void Node::Draw()
    {
        for (auto child : _children)
        {
            if (child.second->GetType() != NodeType::Camera && child.second->GetType() != NodeType::Light)
            {
                child.second->Draw();
            }
        }
    }

    void Node::DrawMetaData()
    {
        for (auto child : _children)
        {
            if (child.second->GetType() != NodeType::Camera && child.second->GetType() != NodeType::Light)
            {
                child.second->DrawMetaData();
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

    NodeType Node::GetType()
    {
        return _type;
    }

    Map<String, SPtr<Node>>& Node::GetChildren()
    {
        return _children;
    }

    void Node::SetScene(SPtr<Scene> scene)
    {
        _scene = scene;
    }

    void Node::SetParent(SPtr<Node> parent)
    {
        _parent = parent;
    }

    void Node::Move(XMVECTOR movement)
    {
        for (auto child : _children)
        {
            switch (child.second->GetType())
            {
            case NodeType::Node:
                child.second->Move(movement);
                break;

            case NodeType::Light:
                child.second->Move(movement);
                break;

            case NodeType::Camera:
                child.second->Move(movement);
                break;

            case NodeType::Model:
                child.second->Move(movement);
                break;
            }
        }

        IMoveable::Move(movement);
    }

    void Node::MoveStrafe(XMVECTOR movement)
    {
        for (auto child : _children)
        {
            switch (child.second->GetType())
            {
            case NodeType::Node:
                child.second->MoveStrafe(movement);
                break;

            case NodeType::Light:
                child.second->MoveStrafe(movement);
                break;

            case NodeType::Camera:
                child.second->MoveStrafe(movement);
                break;

            case NodeType::Model:
                child.second->MoveStrafe(movement);
                break;
            }
        }

        IMoveable::MoveStrafe(movement);
    }

    void Node::Scale(XMVECTOR origin, XMVECTOR scale)
    {
        for (auto child : _children)
        {
            switch (child.second->GetType())
            {
            case NodeType::Node:
                child.second->Scale(origin, scale);
                break;

            case NodeType::Light:
                child.second->Scale(origin, scale);
                break;

            case NodeType::Camera:
                child.second->Scale(origin, scale);
                break;

            case NodeType::Model:
                child.second->Scale(origin, scale);
                break;
            }
        }

        IMoveable::Scale(origin, scale);
    }

    void Node::Scale(XMVECTOR scale)
    {
        XMFLOAT3 position = GetPosition();
        XMVECTOR P = XMLoadFloat3(&position);

        for (auto child : _children)
        {
            switch (child.second->GetType())
            {
            case NodeType::Node:
                child.second->Scale(P, scale);
                break;

            case NodeType::Light:
                child.second->Scale(P, scale);
                break;

            case NodeType::Camera:
                child.second->Scale(P, scale);
                break;

            case NodeType::Model:
                child.second->Scale(P, scale);
                break;
            }
        }

        IMoveable::Scale(scale);
    }

    void Node::Rotate(XMVECTOR origin, XMVECTOR eulerAngles)
    {
        for (auto child : _children)
        {
            switch (child.second->GetType())
            {
            case NodeType::Node:
                child.second->Rotate(origin, eulerAngles);
                break;

            case NodeType::Light:
                child.second->Rotate(origin, eulerAngles);
                break;

            case NodeType::Camera:
                child.second->Rotate(origin, eulerAngles);
                break;

            case NodeType::Model:
                child.second->Rotate(origin, eulerAngles);
                break;
            }
        }

        IMoveable::Rotate(origin, eulerAngles);
    }

    void Node::Rotate(XMVECTOR eulerAngles)
    {
        XMFLOAT3 position = GetPosition();
        XMVECTOR P = XMLoadFloat3(&position);

        for (auto child : _children)
        {
            switch (child.second->GetType())
            {
            case NodeType::Node:
                child.second->Rotate(P, eulerAngles);
                break;

            case NodeType::Light:
                child.second->Rotate(P, eulerAngles);
                break;

            case NodeType::Camera:
                child.second->Rotate(P, eulerAngles);
                break;

            case NodeType::Model:
                child.second->Rotate(P, eulerAngles);
                break;
            }
        }

        IMoveable::Rotate(eulerAngles);
    }
}