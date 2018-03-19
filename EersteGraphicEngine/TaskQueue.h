#pragma once

#include "PrerequisitesUtil.h"
#include "Task.h"

namespace ege
{
    class TaskQueue
    {
    public:
        TaskQueue(std::size_t _maxTasks);
        ~TaskQueue() {}

        bool        Push(SPtr<Task> task);
        SPtr<Task>  Pop();
        SPtr<Task>  Steal();
        std::size_t Size() const;
        bool        Empty() const;

    private:
        std::vector<SPtr<Task>> _tasks;
        std::atomic<int> _top, _bottom;
    };
}