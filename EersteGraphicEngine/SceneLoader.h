#pragma once

#include "PrerequisitesCore.h"

namespace ege
{
    class SceneLoader
    {
    public:
        SceneLoader() {};
        ~SceneLoader() {};

        void Load(String filePath, SPtr<Scene> scene);
    };
}