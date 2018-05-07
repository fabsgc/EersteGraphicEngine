#include "SceneLoader.h"

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

        for (tinyxml2::XMLElement* nodeElement = element->FirstChildElement("node"); nodeElement != nullptr; nodeElement = nodeElement->NextSiblingElement())
        {
            LoadNode(scene, node, nodeElement);
        }

        tinyxml2::XMLElement* entitiesElement = element->FirstChildElement("entities");
        for (tinyxml2::XMLElement* entityElement = entitiesElement->FirstChildElement("entity"); entityElement != nullptr; entityElement = entityElement->NextSiblingElement())
        {
            String type = entityElement->Attribute("type");
            String name = entityElement->Attribute("name");

            if (type == "model")
            {
                LoadEntityModel(node, entityElement);
            }
            else if (type == "light")
            {
                LoadEntityLight(node, entityElement);
            }
            else if (type == "camera")
            {
                LoadEntityCamera(node, entityElement);
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

    void SceneLoader::LoadEntityModel(SPtr<Node> node, tinyxml2::XMLElement* element)
    {
    }

    void SceneLoader::LoadEntityLight(SPtr<Node> node, tinyxml2::XMLElement* element)
    {
    }

    void SceneLoader::LoadEntityCamera(SPtr<Node> node, tinyxml2::XMLElement* element)
    {
    }
}