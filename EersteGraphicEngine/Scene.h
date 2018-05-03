#pragma once

#include "PrerequisitesCore.h"
#include "IDrawable.h"
#include "IUpdatable.h"
#include "Node.h"

namespace ege
{
    class Scene: public IDrawable, public IUpdatable
    {
    public:
        Scene(String filePath);
        ~Scene();

        void Initialise();
        void Update() override;
        void Draw() override;

    private:
        String             _filePath;
        Vector<SPtr<Node>> _nodes;
    };
}