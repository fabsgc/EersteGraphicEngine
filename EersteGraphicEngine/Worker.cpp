#include "Worker.h"

namespace ege
{
    Worker::Worker()
        : _state(WorkerState::Idle)
        , _queue(10)
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

    void Worker::Submit(SPtr<Task> task)
    {
        _queue.Push(task);
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