#pragma once

#include "PrerequisitesUtil.h"
#include "TaskQueue.h"
#include "Task.h"

namespace ege
{
    enum class WorkerState
    {
        Idle, Running, Stopping
    };

    class Worker
    {
    public:
        Worker();
        ~Worker() {}

        void Run();
        void Stop();
        void Submit(SPtr<Task> task);
        void Wait(SPtr<Task> task);
        bool Running();
        std::thread::id GetThreadId();

    private:
        void            Join();
        SPtr<Task>      GetTask();

    private:
        std::thread              _thread;
        std::thread::id          _threadId;
        std::atomic<WorkerState> _state;

        TaskQueue                _queue;
    };
}