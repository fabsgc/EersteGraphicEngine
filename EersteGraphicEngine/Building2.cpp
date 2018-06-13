#include "Building2.h"

#include "ModelManager.h"
#include "Building2Material.h"

namespace ege
{
    Building2::Building2()
        : Model()
    {
    }

    Building2::~Building2()
    {
    }

    void Building2::Initialise()
    {
        Build(gModelManager().GetPtr("building-2"));

        SPtr<Building2Material> material = ege_shared_ptr_new<Building2Material>();
        material->Initialise();
        SetMaterial(material);
    }

    void Building2::Update()
    {
        Model::Update();
    }
}