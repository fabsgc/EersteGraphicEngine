#pragma once

#include "PrerequisitesCore.h"
#include "PointLight.h"
#include "Camera.h"
#include "Model.h"
#include "Light.h"
#include "Scene.h"
#include "Node.h"

namespace ege
{
    class SceneLoader
    {
    public:
        SceneLoader() {};
        ~SceneLoader() {};

        void Load(String filePath, SPtr<Scene> scene);
    
    private:
        void LoadNode(SPtr<Scene> scene, SPtr<Node> parent, tinyxml2::XMLElement* element);
        void LoadEntityModel(SPtr<Node> node, tinyxml2::XMLElement* element);
        void LoadEntityLight(SPtr<Node> node, tinyxml2::XMLElement* element);
        void LoadEntityCamera(SPtr<Node> node, tinyxml2::XMLElement* element);
    };
}