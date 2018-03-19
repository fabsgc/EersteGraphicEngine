#include "TaskQueue.h"

namespace ege
{
    TaskQueue::TaskQueue(std::size_t _maxTasks)
    {
        _tasks.reserve(_maxTasks);
    }

    bool TaskQueue::Push(SPtr<Task> task)
    {
        int bottom = _bottom.load(std::memory_order_acquire);

        if (bottom < static_cast<int>(_tasks.size()))
        {
            _tasks[bottom] = task;
            _bottom.store(bottom + 1, std::memory_order_release);

            return true;
        }
        else
        {
            return false;
        }
    }

    SPtr<Task> TaskQueue::Pop()
    {
        int bottom = _bottom.load(std::memory_order_acquire);
        bottom = std::max(0, bottom - 1);
        _bottom.store(bottom, std::memory_order_release);
        int top = _top.load(std::memory_order_acquire);

        if (top <= bottom)
        {
            SPtr<Task> task = _tasks[bottom];

            if (top != bottom)
            {
                // More than one job left in the queue
                return task;
            }
            else
            {
                int expectedTop = top;
                int desiredTop = top + 1;

                if (!_top.compare_exchange_weak(expectedTop, desiredTop,
                    std::memory_order_acq_rel))
                {
                    // Someone already took the last item, abort
                    task = nullptr;
                }

                _bottom.store(top + 1, std::memory_order_release);
                return task;
            }
        }
        else
        {
            // Queue already empty
            _bottom.store(top, std::memory_order_release);
            return nullptr;
        }
    }

    SPtr<Task> TaskQueue::Steal()
    {
        return nullptr; //TODO
    }

    std::size_t TaskQueue::Size() const
    {
        return _tasks.size();
    }

    bool TaskQueue::Empty() const
    {
        if (_tasks.size() > 0)
        {
            return false;
        }

        return false;
    }
}