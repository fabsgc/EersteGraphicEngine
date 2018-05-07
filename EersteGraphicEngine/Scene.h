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
        Scene();
        ~Scene();

        void         Initialise();
        void         InsertNode(String name, SPtr<Node> node);
        void         InsertLight(String name, SPtr<Light> light);
        void         InsertCamera(String name, SPtr<Camera> camera);
        SPtr<Node>   GetNode(String name);
        SPtr<Light>  GetLight(String name);
        SPtr<Camera> GetCamera(String name);
        SPtr<Camera> GetActiveCamera();
        void         SetActiveCamera(SPtr<Camera> camera);
        void         Update() override;
        void         Draw() override;

    private:
        Map<String, SPtr<Node>>   _nodes;
        Map<String, SPtr<Light>>  _lights;
        Map<String, SPtr<Camera>> _cameras;
        SPtr<Camera>              _camera;
    };
}