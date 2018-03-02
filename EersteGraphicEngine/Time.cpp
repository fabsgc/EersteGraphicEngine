#include "Time.h"

namespace ege
{
    const double Time::MICROSEC_TO_SEC = 1.0 / 1000000.0;

    Time::Time()
        : _run(true)
        , _frameDelta(0.0f)
        , _timeSinceStart(0.0f)
        , _timeSinceStartMs(0)
        , _appStartTime(0)
        , _lastFrameTime(0)
        , _currentFrame(0UL)
    {
        _timer.reset(new Timer());
        _appStartTime = _timer->GetStartMs();
        _lastFrameTime = _timer->GetMicroseconds();
    }

    Time::~Time()
    {
    }

    void Time::Update()
    {
        if (_run)
        {
            UINT64 currentFrameTime = _timer->GetMicroseconds();

            _frameDelta = (float)((currentFrameTime - _lastFrameTime) * MICROSEC_TO_SEC);
            _timeSinceStartMs = (UINT64)(currentFrameTime / 1000);
            _timeSinceStart = _timeSinceStartMs / 1000.0f;

            _lastFrameTime = currentFrameTime;

            _currentFrame.fetch_add(1, std::memory_order_relaxed);
        }
    }

    UINT64 Time::GetTimePrecise() const
    {
        return _timer->GetMicroseconds();
    }

    Time& gTime()
    {
        return Time::Instance();
    }

    void Time::Stop()
    {
        _run = false;
    }

    void Time::Start()
    {
        _run = true;
    }
}
