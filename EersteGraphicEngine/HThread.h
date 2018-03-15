#pragma once

#include "PrerequisitesUtil.h"

namespace ege
{
    class HThread
    {
    public:
        HThread(UINT32 id);
        UINT32  GetId() const;
        Thread& GetThread();
        void    Initialise();

        void    Start(std::function<void()> workerMethod, UINT32 id);
        void    Destroy();
        bool    IsIdle();
        time_t  IdleTime();

        void    BlockUntilComplete();

    private:
        void    Run();

    private:
        UINT32                _id;
        bool                  _idle;
        bool                  _started;
        bool                  _ready;

        time_t                _idleTime;

        Thread*               _thread;
        mutable Mutex         _mutex;
        Signal                _startedCond;
        Signal                _readyCond;
        Signal                _workerEndedCond;

        std::function<void()> _workerMethod;
    };
}