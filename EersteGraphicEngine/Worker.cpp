#include "Worker.h"

namespace ege
{
    Worker::Worker()
        : _state(WorkerState::Idle)
        , _taskScehduler(gTaskScheduler())
    {
    }

    void Worker::Run()
    {
    }

    void Worker::Stop()
    {
    }

    void Worker::Join()
    {
    }

    void Worker::Wait(SPtr<Task> task)
    {
        while (!task->Finished())
        {
            SPtr<Task> task = GetTask();

            if (task != nullptr)
            {
                task->Run();
            }
        }
    }

    bool Worker::Running()
    {
        if (_state == WorkerState::Running)
        {
            return true;
        }

        return false;
    }

    SPtr<Task> Worker::GetTask()
    {
        return nullptr; //TODO
    }

    std::thread::id Worker::GetThreadId()
    {
        return _threadId;
    }
}