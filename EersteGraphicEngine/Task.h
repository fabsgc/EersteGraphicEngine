#pragma once

#include "PrerequisitesUtil.h"

namespace ege
{
    class Task
    {
    public:
        Task();
        ~Task();
        void Run();
        bool Finished() const;
        void Reset(std::function<void()> workerMethod, Task* parent = nullptr);
        void Initialise(std::function<void()> workerMethod, Task* parent = nullptr);

    protected:
        void Finish();

    protected:
        Task*                 _parent;
        std::atomic_size_t    _tasksToRun;
        std::function<void()> _workerMethod;
    };
}