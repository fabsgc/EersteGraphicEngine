#include "Quad.h"

#include "ModelManager.h"
#include "DefaultMaterial.h"

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

        SPtr<DefaultMaterial> material = ege_shared_ptr_new<DefaultMaterial>();
        material->Initialise();
        SetMaterial(material);
    }

    void Quad::Update()
    {
        Model::Update();
    }
}