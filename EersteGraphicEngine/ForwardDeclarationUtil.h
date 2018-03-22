#pragma once

namespace ege
{
    /** Enum used for object construction specifying the object should be zero initializes. */
    enum EGE_ZERO { EgeZero };

    /** Enum used for matrix/quaternion constructor specifying it should be initialized with an identity value. */
    enum EGE_IDENTITY { EgeIdentity };

    class BasicAllocator;
    class LinearAllocator;

    class MemoryCounter;
    class MemoryAllocatorBase;
    class GeneralAllocator;

    class Console;

    class DynamicLib;
    class DynamicLibManager;
    
    template<class T> class IModule;

    class Time;
    class Timer;
}