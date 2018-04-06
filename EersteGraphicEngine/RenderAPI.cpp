#include "RenderAPI.h"

namespace ege
{
    void RenderAPI::OnStartUp()
    {
    };

    void RenderAPI::Initialise()
    {
    }

    void RenderAPI::Reset()
    {
    }

    RenderAPI& gRenderAPI()
    {
        return static_cast<RenderAPI&>(RenderAPI::Instance());
    }

    RenderAPI* gRenderAPIPtr()
    {
        return static_cast<RenderAPI*>(RenderAPI::InstancePtr());
    }
}