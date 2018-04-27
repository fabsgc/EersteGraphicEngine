#pragma once

#include "PrerequisitesUtil.h"
#include "TaskQueue.h"
#include "IModule.h"
#include "Worker.h"

namespace ege
{
    enum class TaskPriority
    {
        Low, Normal, High
    };

    class TaskScheduler: public IModule<TaskScheduler>
    {
    public:
        TaskScheduler(UINT8 tasksPerThread);
        ~TaskScheduler();

        SPtr<Worker> RandomWorker();
        SPtr<Worker> ThreadWorker();

        void Submit(SPtr<Task> task, TaskPriority priority);

        template<class T = TaskScheduler>
        static void StartUp(UINT8 tasksPerThread)
        {
            IModule::StartUp<T>(tasksPerThread);
        }

    private:
        void OnStartUp();
        void OnShutDown() override {};
        SPtr<Worker> FindThreadWorker(const std::thread::id threadId);

    private:
        Vector<SPtr<Worker>>         _workers;
        UINT8                        _numberThreads;
        UINT8                        _tasksPerThread;

        Map<TaskPriority, TaskQueue> _queues;
    };

    TaskScheduler& gTaskScheduler();
}