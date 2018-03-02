#pragma once

#include "PrerequisitesUtil.h"
#include "IModule.h"
#include "DynamicLib.h"

namespace ege
{
    class DynamicLibManager : public IModule<DynamicLibManager>
    {
    public:
        DynamicLibManager();
        virtual ~DynamicLibManager();

        SPtr<DynamicLib> Load(const String& name);
        void Unload(SPtr<DynamicLib> lib);

    protected:
        Map<String, SPtr<DynamicLib>> _loadedLibraries;
    };

    DynamicLibManager& gDynamicLibManager();
}