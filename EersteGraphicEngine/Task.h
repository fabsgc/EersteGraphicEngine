#pragma once

#include "PrerequisitesUtil.h"

namespace ege
{
    enum class TaskState
    {
        Idle, Running, Stopping
    };

    class Task
    {
    public:
        Task();
        ~Task();
        void Run();
        bool Finished() const;
        void Reset(std::function<void()> workerMethod, Task* parent = nullptr);
        void Initialise(std::function<void()> workerMethod, Task* parent = nullptr);

    private:
        void Finish();

    private:
        Task *                _parent;
        std::atomic_size_t    _tasksToRun;
        std::function<void()> _workerMethod;
    };
}