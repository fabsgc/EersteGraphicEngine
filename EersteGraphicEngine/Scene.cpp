#include "Scene.h"

namespace ege
{
    Scene::Scene()
        : _renderAPI(gRenderAPI())
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

    SPtr<Node>& Scene::GetNode(String name)
    {
        auto found = _nodes.find(name);
        EGE_ASSERT_ERROR((found != _nodes.end()), ("Node " + name + " not found"));

        return found->second;
    }

    SPtr<Light>& Scene::GetLight(String name)
    {
        auto found = _lights.find(name);
        EGE_ASSERT_ERROR((found != _lights.end()), ("Light " + name + " not found"));

        return found->second;
    }

    SPtr<Camera>& Scene::GetCamera(String name)
    {
        auto found = _cameras.find(name);
        EGE_ASSERT_ERROR((found != _cameras.end()), ("Camera " + name + " not found"));

        return found->second;
    }

    SPtr<AmbientLight>& Scene::GetAmbientLight()
    {
        return _ambientLight;
    }

    SPtr<Camera>& Scene::GetActiveCamera()
    {
        return _camera;
    }

    void Scene::SetActiveCamera(SPtr<Camera> camera)
    {
        _camera = camera;
    }

    void Scene::SetAmbientLight(SPtr<AmbientLight> ambientLight)
    {
        _ambientLight = ambientLight;
    }

    void Scene::Update()
    {
        if (_ambientLight != nullptr && _ambientLight->IsEnabled())
        {
            _ambientLight->Update();
        }

        for (auto node : _nodes)
        {
            node.second->Update();
        }
    }

    void Scene::Draw()
    {
        DrawCamera();
        DrawLights();
        DrawNodes();
    }

    void Scene::DrawCamera()
    {
        if (_camera != nullptr)
        {
            _camera->Draw();

            ID3D11DeviceContext* context = _renderAPI.GetDevice()->GetImmediateContext();
            ID3D11Buffer* constantBuffer = _renderAPI.GetConstantBuffer(ConstantBufferType::FRAME);
            FrameConstantBuffer* constantBufferUpdate = (FrameConstantBuffer*)gRenderAPI().GetConstantBufferUpdate(ConstantBufferType::FRAME);
            context->UpdateSubresource(constantBuffer, 0, nullptr, constantBufferUpdate, 0, 0);
        }
    }

    void Scene::DrawLights()
    {
        ID3D11DeviceContext* context = _renderAPI.GetDevice()->GetImmediateContext();
        ID3D11Buffer* constantBuffer = _renderAPI.GetConstantBuffer(ConstantBufferType::LIGHT);
        LightConstantBuffer* constantBufferUpdate = (LightConstantBuffer*)gRenderAPI().GetConstantBufferUpdate(ConstantBufferType::LIGHT);

        constantBufferUpdate->LightIndex = 0;

        if (_ambientLight != nullptr && _ambientLight->IsEnabled())
        {
            _ambientLight->Draw();
        }

        for (auto light : _lights)
        {
            if (light.second->IsEnabled())
            {
                light.second->Draw();
            }
        }

        context->UpdateSubresource(constantBuffer, 0, nullptr, constantBufferUpdate, 0, 0);        
    }

    void Scene::DrawNodes()
    {
        for (auto node : _nodes)
        {
            node.second->Draw();
        }
    }
}