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

    void Scene::Update()
    {
        for (auto node : _nodes)
        {
            node->Update();
        }
    }

    void Scene::Draw()
    {
        for (auto node : _nodes)
        {
            node->Draw();
        }
    }
}