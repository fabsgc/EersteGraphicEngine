#include "Node.h"

namespace ege
{
    void Node::Initialise()
    {
    }

    void Node::Update()
    {
        for (auto model : _models)
        {
            model->Update();
        }
    }

    void Node::Draw()
    {
        for (auto model : _models)
        {
            model->Draw();
        }
    }
}