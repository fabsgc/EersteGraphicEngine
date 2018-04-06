#include "Renderer.h"

namespace ege
{
    void Renderer::OnStartUp()
    {
    }

    Renderer& gRenderer()
    {
        return static_cast<Renderer&>(Renderer::Instance());
    }

    Renderer* gRendererPtr()
    {
        return static_cast<Renderer*>(Renderer::InstancePtr());
    }
}