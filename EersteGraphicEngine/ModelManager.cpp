#include "ModelManager.h"

namespace ege
{
    void ModelManager::OnStartUp()
    {
        Initialise();
    }

    void ModelManager::OnShutDown()
    {
    }

    void ModelManager::Initialise()
    {
#if defined(EGE_MODEL_FOLDER) && defined(EGE_CONFIG_MODEL_FILE)
        tinyxml2::XMLDocument document;
        document.LoadFile(EGE_CONFIG_MODEL_FILE);

        tinyxml2::XMLElement* modelsElement = document.FirstChildElement("models");
        EGE_ASSERT_ERROR((modelsElement != nullptr), "Model file malformed");

        for (tinyxml2::XMLElement* modelElement = modelsElement->FirstChildElement("model"); modelElement != nullptr; modelElement = modelElement->NextSiblingElement())
        {
            SPtr<ModelDesc> modelDesc = ege_shared_ptr_new<ModelDesc>();
            
            String name = modelElement->Attribute("name");
            String filePath = modelElement->Attribute("file");

            _modelLoader.Load(EGE_MODEL_FOLDER + filePath, modelDesc);
            Insert(name, modelDesc);
        }
#endif
    }

    void ModelManager::Load(String filePath, String name)
    {
        SPtr<ModelDesc> modelDesc;

        _modelLoader.Load(filePath, modelDesc);
        Insert(name, modelDesc);
    }

    void ModelManager::Get(String name, Model& model)
    {
        auto found = _resources.find(name);
        EGE_ASSERT_ERROR_SHORT(found != _resources.end());

        model.Build(found->second);
    }

    void ModelManager::Get(String name, Geometry& geometry)
    {
        auto found = _resources.find(name);
        EGE_ASSERT_ERROR_SHORT(found != _resources.end());

        geometry.Build(found->second);
    }

    ModelManager& gModelManager()
    {
        return static_cast<ModelManager&>(ModelManager::Instance());
    }

    ModelManager* gModelManagerPtr()
    {
        return static_cast<ModelManager*>(ModelManager::InstancePtr());
    }
}