#include "Scene.h"

namespace ege
{
    Scene::Scene(String filePath)
        : _filePath(filePath)
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

    SPtr<Camera> Scene::GetCamera()
    {
        return _camera;
    }

    void Scene::SetCamera(SPtr<Camera> camera)
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
        for (auto node : _nodes)
        {
            node.second->Draw();
        }
    }
}