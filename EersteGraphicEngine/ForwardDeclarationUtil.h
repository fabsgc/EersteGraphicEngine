#pragma once

namespace ege
{
    /** Enum used for object construction specifying the object should be zero initializes. */
    enum EGE_ZERO { EgeZero };

    /** Enum used for matrix/quaternion constructor specifying it should be initialized with an identity value. */
    enum EGE_IDENTITY { EgeIdentity };

    class BasicAllocator;
    class LinearAllocator;
    template<size_t ElementSize, size_t ElementsPerBlock, size_t Alignment> class PoolAllocator;
    class StackAllocator;

    class MemoryCounter;
    class MemoryAllocatorBase;
    class GeneralAllocator;

    class Console;

    class DynamicLib;
    class DynamicLibManager;
    
    template<class T> class IModule;

    class Time;
    class Timer;

    class Task;
    class TaskQueue;
    class TaskScheduler;
    class Worker;

    class MathUtility;
}