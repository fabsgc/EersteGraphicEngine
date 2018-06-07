#include "Landscape.h"

#include "ModelManager.h"
#include "DefaultMaterial.h"

namespace ege
{
    Landscape::Landscape()
        : Model()
    {
    }

    Landscape::~Landscape()
    {
    }

    void Landscape::Initialise()
    {
        Build(gModelManager().GetPtr("landscape"));

        SPtr<DefaultMaterial> material = ege_shared_ptr_new<DefaultMaterial>();
        material->Initialise();
        SetMaterial(material);
    }

    void Landscape::Update()
    {
        Model::Update();
    }
}