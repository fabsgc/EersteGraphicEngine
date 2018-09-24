#include "Scene.h"

#include "Model.h"

namespace ege
{
    Scene::Scene()
        : _renderAPI(gRenderAPI())
    {}

    Scene::~Scene() 
    {}

    void Scene::Initialise()
    {}

    /*void Scene::InsertNode(String name, SPtr<Node> node)
    {
        //_nodes.insert(Pair<String, SPtr<Node>>(name, std::move(node)));
    }*/

	void Scene::InsertModel(String name, SPtr<Model> model)
	{
		_models.insert(Pair<String, SPtr<Model>>(name, std::move(model)));
	}

    void Scene::InsertLight(String name, SPtr<Light> light)
    {
        _lights.insert(Pair<String, SPtr<Light>>(name, std::move(light)));
    }

    void Scene::InsertCamera(String name, SPtr<Camera> camera)
    {
        _cameras.insert(Pair<String, SPtr<Camera>>(name, std::move(camera)));
    }

    /*SPtr<Node>& Scene::GetNode(String name)
    {
        auto found = _nodes.find(name);
        EGE_ASSERT_ERROR((found != _nodes.end()), ("Node " + name + " not found"));

        return found->second;
    }*/

	SPtr<Model>& Scene::GetModel(String name)
	{
		auto found = _models.find(name);
		EGE_ASSERT_ERROR((found != _models.end()), ("Light " + name + " not found"));

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

		auto update = [](auto elements) {
			for (auto element : elements)
			{
				element.second->Update();
			}
		};

		update(_cameras);
		update(_lights);
		update(_models);
    }

    void Scene::Draw()
    {
        DrawCamera();
        DrawLights();
        DrawModels();
    }

    void Scene::DrawMetaData()
    {
        DrawCamera();
        DrawMetaDataLights();
		DrawMetaDataModels();
    }

    void Scene::DrawCamera()
    {
        if (_camera != nullptr)
        {
            _camera->Draw();

            ID3D11DeviceContext* context = _renderAPI.GetDevice()->GetImmediateContext();
            SPtr<ConstantBufferElement> constantBuffer = _renderAPI.GetConstantBufferPtr(ConstantBufferType::FRAME);
            FrameConstantBuffer* constantBufferUpdate = (FrameConstantBuffer*)&*constantBuffer->UpdateBuffer;
            context->UpdateSubresource(constantBuffer->Buffer, 0, nullptr, constantBufferUpdate, 0, 0);
        }
    }

    void Scene::DrawLights()
    {
        ID3D11DeviceContext* context = _renderAPI.GetDevice()->GetImmediateContext();
        SPtr<ConstantBufferElement> constantBuffer = _renderAPI.GetConstantBufferPtr(ConstantBufferType::LIGHT);
        LightConstantBuffer* constantBufferUpdate = (LightConstantBuffer*)&*constantBuffer->UpdateBuffer;

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

        context->UpdateSubresource(constantBuffer->Buffer, 0, nullptr, constantBufferUpdate, 0, 0);        
    }

	void Scene::DrawModels()
	{
		for (auto model : _models)
		{
			model.second->Draw();
		}
	}

    void Scene::DrawMetaDataLights()
    {
        ID3D11DeviceContext* context = _renderAPI.GetDevice()->GetImmediateContext();
        SPtr<ConstantBufferElement> constantBuffer = _renderAPI.GetConstantBufferPtr(ConstantBufferType::LIGHT);
        LightConstantBuffer* constantBufferUpdate = (LightConstantBuffer*)&*constantBuffer->UpdateBuffer;

        constantBufferUpdate->LightIndex = 0;

        if (_ambientLight != nullptr && _ambientLight->IsEnabled())
        {
            _ambientLight->Draw();
        }

        for (auto light : _lights)
        {
            if (light.second->IsEnabled())
            {
                light.second->DrawMetaData();
            }
        }

        context->UpdateSubresource(constantBuffer->Buffer, 0, nullptr, constantBufferUpdate, 0, 0);
    }

	void Scene::DrawMetaDataModels()
	{
		for (auto model : _models)
		{
			model.second->DrawMetaData();
		}
	}

    /*void Scene::DrawNodes()
    {
        for (auto node : _nodes)
        {
            node.second->Draw();
        }

		for (auto models : _instancedModels)
		{
			for (auto model : models.second)
			{
				model->Draw();
			}
		}

		for (auto model : _nonInstancedModels)
		{
			model->Draw();
		}
    }

    void Scene::DrawMetaDataNodes()
    {
        for (auto node : _nodes)
        {
            node.second->DrawMetaData();
        }

		for (auto models : _instancedModels)
		{
			for (auto model : models.second)
			{
				model->DrawMetaData();
			}
		}

		for (auto model : _nonInstancedModels)
		{
			model->DrawMetaData();
		}
    }

	void Scene::CreateDrawList()
	{
		for (auto node : _nodes)
		{
			CreateDrawListFromNode(node.second);
		}
	}

	void Scene::CreateDrawListFromNode(SPtr<Node> node)
	{
		if (node->GetType() == NodeType::Model)
		{
			SPtr<Model> model = std::static_pointer_cast<Model>(node);

			if (model->GetStatic())
			{
				Pair<SPtr<Material>, SPtr<ModelDesc>> modelPair;

				SPtr<ModelDesc> modelDesc = model->GetModelDesc();
				SPtr<Material>  material  = model->GetMaterial();

				modelPair = std::make_pair<>(material, modelDesc);

				_instancedModels[modelPair].push_back(model);
			}
			else
			{
				_nonInstancedModels.push_back(model);
			}
		}

		Map<String, SPtr<Node>> children = node->GetChildren();

		if (children.size() > 0)
		{
			for (auto child : children)
			{
				CreateDrawListFromNode(child.second);
			}
		}
	}

    Map<String, SPtr<Node>>& Scene::GetNodes()
    {
        return _nodes;
    }*/

	Map<String, SPtr<Model>>& Scene::GetModels()
	{
		return _models;
	}

    Map<String, SPtr<Light>>& Scene::GetLights()
    {
        return _lights;
    }
}