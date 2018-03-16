#include "Worker.h"

namespace ege
{
    Worker::Worker()
        : _state(WorkerState::Idle)
    {
    }

    Worker::~Worker()
    {
    }
}