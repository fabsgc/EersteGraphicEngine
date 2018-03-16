#pragma once

#include "PrerequisitesUtil.h"

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
        ~Worker();

    private:
        WorkerState _state;
    };
}