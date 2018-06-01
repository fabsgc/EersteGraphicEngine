#include "SceneLoader.h"

#include "ShaderManager.h"
#include "ModelManager.h"
#include "PointLight.h"
#include "Shader.h"
#include "Camera.h"
#include "Model.h"
#include "Light.h"
#include "Scene.h"
#include "Node.h"

namespace ege
{
    void SceneLoader::Load(String filePath, SPtr<Scene> scene)
    {
#if defined(EGE_SCENE_FOLDER)
        String path = EGE_SCENE_FOLDER + filePath;
        tinyxml2::XMLDocument document;
        document.LoadFile(path.c_str());

        tinyxml2::XMLElement* sceneElement = document.FirstChildElement("scene");
        EGE_ASSERT_ERROR((sceneElement != nullptr), "Scene file malformed");

        tinyxml2::XMLElement* nodesElement = sceneElement->FirstChildElement("nodes");
        for (tinyxml2::XMLElement* nodeElement = nodesElement->FirstChildElement("node"); nodeElement != nullptr; nodeElement = nodeElement->NextSiblingElement())
        {
            LoadNode(scene, nullptr, nodeElement);
        }
#endif
    }

    void SceneLoader::LoadNode(SPtr<Scene> scene, SPtr<Node> parent, tinyxml2::XMLElement* element)
    {
        SPtr<Node> node = ege_shared_ptr_new<Node>();
        String name = element->Attribute("name");

        tinyxml2::XMLElement* nodesElement = element->FirstChildElement("nodes");
        if (nodesElement != nullptr)
        {
            for (tinyxml2::XMLElement* nodeElement = nodesElement->FirstChildElement("node"); nodeElement != nullptr; nodeElement = nodeElement->NextSiblingElement())
            {
                LoadNode(scene, node, nodeElement);
            }
        }

        tinyxml2::XMLElement* propertiesElement = element->FirstChildElement("properties");
        if (nodesElement != nullptr)
        {
            for (tinyxml2::XMLElement* propertyElement = nodesElement->FirstChildElement("property"); propertyElement != nullptr; propertyElement = propertyElement->NextSiblingElement())
            {

            }
        }

        tinyxml2::XMLElement* entitiesElement = element->FirstChildElement("entities");
        if (entitiesElement != nullptr)
        {
            for (tinyxml2::XMLElement* entityElement = entitiesElement->FirstChildElement("entity"); entityElement != nullptr; entityElement = entityElement->NextSiblingElement())
            {
                String type = entityElement->Attribute("type");

                if (type == "model")
                {
                    LoadEntityModel(scene, node, entityElement);
                }
                else if (type == "light")
                {
                    LoadEntityLight(scene, node, entityElement);
                }
                else if (type == "camera")
                {
                    LoadEntityCamera(scene, node, entityElement);
                }
            }
        }

        if (parent != nullptr)
        {
            parent->InsertNode(name, node);
        }
        else
        {
            scene->InsertNode(name, node);
        }
    }

    void SceneLoader::LoadEntityModel(SPtr<Scene> scene, SPtr<Node> node, tinyxml2::XMLElement* element)
    {
        SPtr<Model> model = ege_shared_ptr_new<Model>();
        String name = element->Attribute("name");

        tinyxml2::XMLElement* propertiesElement = element->FirstChildElement("properties");
        if (propertiesElement != nullptr)
        {
            for (tinyxml2::XMLElement* propertyElement = propertiesElement->FirstChildElement("property"); propertyElement != nullptr; propertyElement = propertyElement->NextSiblingElement())
            {
                String key = propertyElement->Attribute("key");
                String value = propertyElement->Attribute("value");

                if (key == "shader")
                {
                    model->SetShader(gShaderManager().GetPtr(value));
                }
                else if (key == "model")
                {
                    model->Build(gModelManager().GetPtr(value));
                }
            }
        }

        node->InsertEntity(name, model);
    }

    void SceneLoader::LoadEntityLight(SPtr<Scene> scene, SPtr<Node> node, tinyxml2::XMLElement* element)
    {
        SPtr<Light> light = nullptr;
        String name = element->Attribute("name");
        String sort = element->Attribute("sort");

        if (sort == "point")
        {
            light = ege_shared_ptr_new<PointLight>();
        }
        else
        {
            EGE_ASSERT_ERROR(false, "The light type " + sort + " does not exist");
        }

        tinyxml2::XMLElement* propertiesElement = element->FirstChildElement("properties");
        if (propertiesElement != nullptr)
        {
            for (tinyxml2::XMLElement* propertyElement = propertiesElement->FirstChildElement("property"); propertyElement != nullptr; propertyElement = propertyElement->NextSiblingElement())
            {
                String key = propertyElement->Attribute("key");
                String value = propertyElement->Attribute("value");
            }
        }

        scene->InsertLight(name, light);
        node->InsertEntity(name, light);
    }

    void SceneLoader::LoadEntityCamera(SPtr<Scene> scene, SPtr<Node> node, tinyxml2::XMLElement* element)
    {
        SPtr<Camera> camera = ege_shared_ptr_new<Camera>();
        String name = element->Attribute("name");

        tinyxml2::XMLElement* propertiesElement = element->FirstChildElement("properties");
        if (propertiesElement != nullptr)
        {
            for (tinyxml2::XMLElement* propertyElement = propertiesElement->FirstChildElement("property"); propertyElement != nullptr; propertyElement = propertyElement->NextSiblingElement())
            {
                String key = propertyElement->Attribute("key");
                String value = propertyElement->Attribute("value");

                if (key == "default-camera")
                {
                    scene->SetActiveCamera(camera);
                }
            }
        }

        scene->InsertCamera(name, camera);
        node->InsertEntity(name, camera);
    }
}