#pragma once

#include "PrerequisitesCore.h"

namespace ege
{
    template <typename Resource>
    class IResourceManager
    {
    public:
        IResourceManager() {}
        ~IResourceManager() {}
        virtual void Initialise() = 0;

        void Insert(String name, SPtr<Resource> resource)
        {
            _resources.insert(Pair<String, SPtr<Resource>>(name, resource));
        }

        Resource& Get(std::string name)
        {
            auto found = _resources.find(name);
            EGE_ASSERT_ERROR(found != _resources.end(), ("Resource " + name + " not found"));

            return *found->second;
        }

        SPtr<Resource> GetPtr(std::string name)
        {
            auto found = _resources.find(name);
            EGE_ASSERT_ERROR(found != _resources.end(), ("Resource " + name + " not found"));

            return found->second;
        }

    protected:
        Map<String, SPtr<Resource>> _resources;
    };
}