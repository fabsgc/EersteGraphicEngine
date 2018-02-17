#include "Timer.h"

using namespace std::chrono;

namespace ee
{
    Timer::Timer()
    {
        Reset();
    }

    void Timer::Reset()
    {
        _startTime = _HRClock.now();
    }

    UINT64 Timer::GetMilliseconds() const
    {
        auto nextTime = _HRClock.now();
        duration<double> dur = nextTime - _startTime;

        return duration_cast<milliseconds>(dur).count();
    }

    UINT64 Timer::GetMicroseconds() const
    {
        auto nextTime = _HRClock.now();
        duration<double> dur = nextTime - _startTime;

        return duration_cast<microseconds>(dur).count();
    }

    UINT64 Timer::GetStartMs() const
    {
        nanoseconds startTimeNs = _startTime.time_since_epoch();

        return duration_cast<milliseconds>(startTimeNs).count();
    }
}
