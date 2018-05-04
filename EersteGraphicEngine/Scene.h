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

        void         Initialise();
        void         InsertNode(String name, SPtr<Node> node);
        void         InsertLight(String name, SPtr<Light> light);
        SPtr<Node>   GetNode(String name);
        SPtr<Light>  GetLight(String name);
        SPtr<Camera> GetCamera();
        void         SetCamera(SPtr<Camera> camera);
        void         Update() override;
        void         Draw() override;

    private:
        String                   _filePath;
        Map<String, SPtr<Node>>  _nodes;
        Map<String, SPtr<Light>> _lights;
        SPtr<Camera>             _camera;
    };
}