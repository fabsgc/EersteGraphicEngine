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

    private:
        void OnStartUp() override;
        void OnShutDown() override;

    private:
        int _hCrtIn;
        int _hCrtOut;
    };

    Console& gConsole();
}