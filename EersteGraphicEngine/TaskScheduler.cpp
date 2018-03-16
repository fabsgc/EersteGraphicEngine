#include "TaskScheduler.h"

namespace ege
{
    void TaskScheduler::OnStartUp()
    {
    }

    void TaskScheduler::OnShutDown()
    {   
    }
    TaskScheduler& gScheduler()
    {
        return TaskScheduler::Instance();
    }
}