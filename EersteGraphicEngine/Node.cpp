#include "Node.h"

namespace ege
{
    Node::Node()
    {
    }
    
    Node::~Node()
    {
    }

    void Node::Initialise()
    {
    }

    void Node::Update()
    {
        for (auto child : _child)
        {
            child->Update();
        }

        for (auto entity : _entities)
        {
            entity->Update();
        }
    }

    void Node::Draw()
    {
        for (auto child : _child)
        {
            child->Draw();
        }

        for (auto entity : _entities)
        {
            entity->Draw();
        }
    }
}