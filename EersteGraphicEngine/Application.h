#pragma once

#include "PrerequisitesCore.h"
#include "CoreApplication.h"

namespace ege
{
    class Application : public CoreApplication
    {
    public:

    private:
    };

    Application& gApplication();
    Application* gApplicationPtr();
}