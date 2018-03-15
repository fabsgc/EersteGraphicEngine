#include "HThread.h"

namespace ege
{
    HThread::HThread(UINT32 id)
        : _id(id)
        , _idle(true)
        , _started(false)
        , _ready(false)
        , _idleTime(0)
    {}

    UINT32 HThread::GetId() const
    {
        Lock lock(_mutex);
        return _id;
    }

    Thread& HThread::GetThread()
    {
        Lock lock(_mutex);
        return *_thread;
    }

    void HThread::Start(std::function<void()> workerMethod, UINT32 id)
    {
        {
            Lock lock(_mutex);

            _workerMethod = workerMethod;
            _idle = false;
            _idleTime = std::time(nullptr);
            _ready = true;
            _id = id;
        }

        _readyCond.notify_one();
    }

    void HThread::Destroy()
    {
        BlockUntilComplete();

        {
            Lock lock(_mutex);
            _workerMethod = nullptr;
            _ready = true;
        }

        _readyCond.notify_one();
        _thread->join();
    }

    bool HThread::IsIdle()
    {
        Lock lock(_mutex);
        return _idle;
    }

    time_t HThread::IdleTime()
    {
        Lock lock(_mutex);
        return (time(nullptr) - _idleTime);
    }

    void HThread::BlockUntilComplete()
    {
        Lock lock(_mutex);

        while (!_idle)
            _workerEndedCond.wait(lock);
    }

    void HThread::Initialise()
    {
        _thread = ege_new<Thread>(std::bind(&HThread::Run, this));

        Lock lock(_mutex);

        while (!_started)
            _startedCond.wait(lock);
    }

    void HThread::Run()
    {
    }
}