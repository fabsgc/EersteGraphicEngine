#pragma once

#include "PrerequisitesUtil.h"
#include "IModule.h"
#include "Worker.h"

namespace ege
{
    class TaskScheduler: public IModule<TaskScheduler>
    {
    public:
        TaskScheduler(UINT8 tasksPerThread);
        ~TaskScheduler();

        SPtr<Worker> RandomWorker();
        SPtr<Worker> ThreadWorker();

        template<class T = TaskScheduler>
        static void StartUp(UINT8 tasksPerThread)
        {
            IModule::StartUp<T>(tasksPerThread);
        }

    private:
        void OnStartUp() override {};
        void OnShutDown() override {};

    private:
        Vector<SPtr<Worker>> _workers;
        UINT8                _numberThreads;
        UINT8                _tasksPerThread;
        

        SPtr<Worker> FindThreadWorker(const std::thread::id threadId);
    };

    TaskScheduler& gScheduler();
}