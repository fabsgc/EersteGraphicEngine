#pragma once

#include "PrerequisitesCore.h"
#include "IUpdatable.h"
#include "IDrawable.h"
#include "Camera.h"
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
        String              _filePath;
        Vector<SPtr<Node>>  _nodes;
        Vector<SPtr<Light>> _lights;
        SPtr<Camera>        _camera;
    };
}