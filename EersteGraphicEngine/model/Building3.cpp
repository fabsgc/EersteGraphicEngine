#include "Building3.h"

#include "ModelManager.h"
#include "Building3Material.h"

namespace ege
{
    Building3::Building3()
        : Model()
    {
    }

    Building3::~Building3()
    {
    }

    void Building3::Initialise()
    {
        Build(gModelManager().GetPtr("building-3"));

        SPtr<Building3Material> material = ege_shared_ptr_new<Building3Material>();
        material->Initialise();
        SetMaterial(material);
    }

    void Building3::Update()
    {
        Model::Update();
    }
}