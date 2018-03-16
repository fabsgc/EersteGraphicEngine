#include "Task.h"

namespace ege
{
    Task::Task()
        : _tasksToRun(0)
    {
    }

    Task::~Task()
    {
        _parent = nullptr;
    }

    void Task::Initialise(std::function<void()> workerMethod, Task* parent)
    {
        _workerMethod = workerMethod;
        _parent       = parent;
        _tasksToRun   = 1;
        
        if (parent != nullptr)
        {
            parent->_tasksToRun++;
        }
    }

    void Task::Reset(std::function<void()> workerMethod, Task* parent)
    {
        Initialise(workerMethod, parent);
    }

    void Task::Run()
    {
        _workerMethod();
        Finish();
    }

    bool Task::Finished() const
    {
        return _tasksToRun == 0;
    }

    void Task::Finish()
    {
        _tasksToRun--;

        if (Finished())
        {
            if (_parent != nullptr)
            {
                _parent->Finish();
            }
        }
    }
}