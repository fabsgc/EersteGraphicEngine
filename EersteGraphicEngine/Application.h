#pragma once

#include "PrerequisitesCore.h"
#include "CoreApplication.h"

namespace ege
{
    class Application : public CoreApplication
    {
    public:
        Application(const StartUpDescription& desc);
        ~Application();

        template<class T = Application>
        static void StartUp(const StartUpDescription& desc)
        {
            CoreApplication::StartUp<T>(desc);
        }

        void RunMainLoop() override;
        void Update() override;
        void Draw() override;

    private:
        void OnStartUp() override;
        void OnShutDown() override;

        void SceneLoader() override;
    };

    Application& gApplication();
    Application* gApplicationPtr();
}