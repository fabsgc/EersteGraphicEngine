#pragma once

#include "PrerequisitesUtil.h"

namespace ee
{
    class Timer
    {
    public:
        Timer();
        void   Reset();
        UINT64 GetMilliseconds() const;
        UINT64 GetMicroseconds() const;
        UINT64 GetStartMs() const;

    private:
        std::chrono::high_resolution_clock                          _HRClock;
        std::chrono::time_point<std::chrono::high_resolution_clock> _startTime;
    };
}
