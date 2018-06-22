#pragma once

#include "PrerequisitesUtil.h"
#include "IModule.h"

namespace ege
{
    class Console: public IModule<Console>
    {
    public:
        Console() {}
        ~Console() {}

    protected:
        void OnStartUp() override;
        void OnShutDown() override;

    protected:
        int _hCrtIn;
        int _hCrtOut;
    };

    Console& gConsole();
}