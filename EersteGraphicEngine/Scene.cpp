#include "Scene.h"

namespace ege
{
    Scene::Scene()
    {
    }

    Scene::~Scene() 
    {
    }

    void Scene::Initialise()
    {
    }

    void Scene::InsertNode(String name, SPtr<Node> node)
    {
        _nodes.insert(Pair<String, SPtr<Node>>(name, std::move(node)));
    }

    void Scene::InsertLight(String name, SPtr<Light> light)
    {
        _lights.insert(Pair<String, SPtr<Light>>(name, std::move(light)));
    }

    void Scene::InsertCamera(String name, SPtr<Camera> camera)
    {
        _cameras.insert(Pair<String, SPtr<Camera>>(name, std::move(camera)));
    }

    SPtr<Node> Scene::GetNode(String name)
    {
        auto found = _nodes.find(name);
        EGE_ASSERT_ERROR((found != _nodes.end()), ("Node " + name + " not found"));

        return found->second;
    }

    SPtr<Light> Scene::GetLight(String name)
    {
        auto found = _lights.find(name);
        EGE_ASSERT_ERROR((found != _lights.end()), ("Light " + name + " not found"));

        return found->second;
    }

    SPtr<Camera> Scene::GetCamera(String name)
    {
        auto found = _cameras.find(name);
        EGE_ASSERT_ERROR((found != _cameras.end()), ("Camera " + name + " not found"));

        return found->second;
    }

    SPtr<Camera> Scene::GetActiveCamera()
    {
        return _camera;
    }

    void Scene::SetActiveCamera(SPtr<Camera> camera)
    {
        _camera = camera;
    }

    void Scene::Update()
    {
        for (auto node : _nodes)
        {
            node.second->Update();
        }
    }

    void Scene::Draw()
    {
        if (_camera != nullptr)
        {
            _camera->Draw();
        }
       
        for (auto node : _nodes)
        {
            node.second->Draw();
        }
    }
}