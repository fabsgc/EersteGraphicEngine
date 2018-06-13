#include "Cube.h"

#include "ModelManager.h"
#include "Building1Material.h"

#include "Building1.h"

namespace ege
{
    Building1::Building1()
        : Model()
    {
    }

    Building1::~Building1()
    {
    }

    void Building1::Initialise()
    {
        Build(gModelManager().GetPtr("building-1"));

        SPtr<Building1Material> material = ege_shared_ptr_new<Building1Material>();
        material->Initialise();
        SetMaterial(material);
    }

    void Building1::Update()
    {
        Model::Update();
    }
}