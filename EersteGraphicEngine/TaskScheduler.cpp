#include "TaskScheduler.h"

namespace ege
{
    TaskScheduler::TaskScheduler(UINT8 tasksPerThread)
        : _numberThreads(EGE_THREAD_HARDWARE_CONCURRENCY - 1)
        , _tasksPerThread(tasksPerThread)
    {
        _workers.reserve(_numberThreads);

        for (UINT8 i = 0; i < _numberThreads; ++i)
        {
            auto worker = ege_shared_ptr_new<Worker>();
            _workers.push_back(worker);
        }

        for (auto& worker : _workers)
        {
            worker->Run();
        }
    }

    TaskScheduler::~TaskScheduler()
    {
        _workers.clear();
    }

    SPtr<Worker> TaskScheduler::RandomWorker()
    {
        std::uniform_int_distribution<std::size_t> dist{ 0, _workers.size() };
        std::default_random_engine randomEngine{ std::random_device()() };

        SPtr<Worker> worker = _workers[dist(randomEngine)];

        if (worker->Running())
        {
            return worker;
        }

        return nullptr;
    }

    SPtr<Worker> TaskScheduler::ThreadWorker()
    {
        return FindThreadWorker(std::this_thread::get_id());
    }

    SPtr<Worker> TaskScheduler::FindThreadWorker(const std::thread::id threadId)
    {
        for (auto& worker : _workers)
        {
            if (worker->GetThreadId() == threadId)
            {
                return worker;
            }
        }

        return nullptr;
    }

    void TaskScheduler::Submit(SPtr<Task> task, TaskPriority priority)
    {
        _queues[priority].Push(task);
    }

    TaskScheduler& gTaskScheduler()
    {
        return TaskScheduler::Instance();
    }
}