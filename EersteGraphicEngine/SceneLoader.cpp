#include "SceneLoader.h"
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
        /*SPtr<Node> node = ege_shared_ptr_new<Node>();
        String name = element->Attribute("name");

        tinyxml2::XMLElement* nodesElement = element->FirstChildElement("nodes");
        if (nodesElement != nullptr)
        {
            for (tinyxml2::XMLElement* nodeElement = nodesElement->FirstChildElement("node"); nodeElement != nullptr; nodeElement = nodeElement->NextSiblingElement())
            {
                LoadNode(scene, node, nodeElement);
            }
        }

        if (parent != nullptr)
        {
            parent->InsertNode(name, node);
        }
        else
        {
            scene->InsertNode(name, node);
        }*/
    }

    void SceneLoader::LoadEntityModel(SPtr<Scene> scene, SPtr<Node> node, tinyxml2::XMLElement* element)
    {}

    void SceneLoader::LoadEntityLight(SPtr<Scene> scene, SPtr<Node> node, tinyxml2::XMLElement* element)
    {}

    void SceneLoader::LoadEntityCamera(SPtr<Scene> scene, SPtr<Node> node, tinyxml2::XMLElement* element)
    {}
}