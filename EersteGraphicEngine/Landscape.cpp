#include "Landscape.h"

#include "ModelManager.h"
#include "LandscapeMaterial.h"

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

        SPtr<LandscapeMaterial> material = ege_shared_ptr_new<LandscapeMaterial>();
        material->Initialise();
        SetMaterial(material);
    }

    void Landscape::Update()
    {
        Model::Update();
    }
}