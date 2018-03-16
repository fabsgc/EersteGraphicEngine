#pragma once

#include "PrerequisitesUtil.h"
#include "IModule.h"

namespace ege
{
    class TaskScheduler: public IModule<TaskScheduler>
    {
    public:
        TaskScheduler() {}
        ~TaskScheduler() {}

    private:
        void OnStartUp() override;
        void OnShutDown() override;

    private:
    };

    TaskScheduler& gScheduler();
}