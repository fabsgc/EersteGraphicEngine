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
            tinyxml2::XMLElement* entitiesElement = nodeElement->FirstChildElement("entities");
            for (tinyxml2::XMLElement* entityElement = entitiesElement->FirstChildElement("entity"); entityElement != nullptr; entityElement = entityElement->NextSiblingElement())
            {
            }
        }
#endif
    }

    void SceneLoader::LoadNode(SPtr<Scene> scene, SPtr<Node> parent, tinyxml2::XMLElement* element)
    {
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