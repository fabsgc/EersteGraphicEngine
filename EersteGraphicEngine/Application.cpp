#include "Application.h"

namespace ege
{
    Application& gApplication()
    {
        return Application::Instance();
    }

    Application* gCoreApplicationPtr()
    {
        return Application::InstancePtr();
    }
}