#pragma once

#include "PrerequisitesCore.h"
#include "DynamicLibManager.h"
#include "IModule.h"

namespace ege
{
    struct START_UP_DESC
    {
    };

    class CoreApplication : IModule<CoreApplication>
    {
    public:
        CoreApplication();
        ~CoreApplication();

        void RunMainLoop();
        void StopMainLoop();

        template<class T = CoreApplication>
        static void StartUp(const START_UP_DESC& desc)
        {
            IModule::StartUp<T>(desc);
        }

    protected:
        void OnStartUp() override;
        void OnShutDown() override;

        void StartUpRenderAPI();
        void StartUpRenderer();
        void StartUpWindow();

    protected:
        volatile bool _runMainLoop;
    };
}