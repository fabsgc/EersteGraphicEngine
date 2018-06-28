#include "Quad.h"

#include "ModelManager.h"

namespace ege
{
    Quad::Quad()
        : Model()
    {
    }

    Quad::~Quad()
    {
    }

    void Quad::Initialise()
    {
        Build(gModelManager().GetPtr("quad"));
    }

    void Quad::Update()
    {
        Model::Update();
    }
}