#pragma once

#include "PrerequisitesUtil.h"

namespace ege
{
    template<class T>
    class IModule
    {
    public:
        template<class ...Args>
        static void StartUp(Args &&...args)
        {
            EGE_ASSERT_ERROR(!IsStartedUp(), "Trying to start an already started module.");

            _instance() = new T(std::forward<Args>(args)...);
            IsStartedUp() = true;

            ((IModule*)_instance())->OnStartUp();
        }

        template<class SubType, class ...Args>
        static void StartUp(Args &&...args)
        {
            static_assert(std::is_base_of<T, SubType>::value, "Provided type is not derived from type the Module is initialized with.");
            EGE_ASSERT_ERROR(!IsStartedUp(), "Trying to start an already started module.");

            _instance() = new SubType(std::forward<Args>(args)...);
            IsStartedUp() = true;

            ((IModule*)_instance())->OnStartUp();
        }

        static void ShutDown()
        {
            EGE_ASSERT_ERROR(!IsDestroyed(), "Trying to shut down an already shut down module.");
            EGE_ASSERT_ERROR(IsStartedUp(), "Trying to shut down a module which was never started.");

            ((IModule*)_instance())->OnShutDown();

            delete _instance();
            IsDestroyed() = true;
        }

        static bool IsStarted()
        {
            return IsStartedUp() && !IsDestroyed();
        }

        static T& Instance()
        {
            EGE_ASSERT_ERROR(IsStartedUp(), "Trying to access a module but it hasn't been started up yet.");
            EGE_ASSERT_ERROR(!IsDestroyed(), "Trying to access a destroyed module.");

            return *_instance();
        }

        static T* InstancePtr()
        {
            EGE_ASSERT_ERROR(IsStartedUp(), "Trying to access a module but it hasn't been started up yet.");
            EGE_ASSERT_ERROR(!IsDestroyed(), "Trying to access a destroyed module.");

            return _instance();
        }

    protected:
        IModule() {}
        virtual ~IModule() {};

        IModule(IModule const&) {};
        IModule& operator=(const IModule&) { return *this; }

        virtual void OnStartUp() {}
        virtual void OnShutDown() {}

        static T*& _instance()
        {
            static T* inst = nullptr;
            return inst;
        }

        static bool& IsDestroyed()
        {
            static bool inst = false;
            return inst;
        }

        static bool& IsStartedUp()
        {
            static bool inst = false;
            return inst;
        }
    };
}
