#include "Shop1.h"

#include "ModelManager.h"
#include "Shop1Material.h"

namespace ege
{
    Shop1::Shop1()
        : Model()
    {
    }

    Shop1::~Shop1()
    {
    }

    void Shop1::Initialise()
    {
        Build(gModelManager().GetPtr("shop-1"));

        SPtr<Shop1Material> material = ege_shared_ptr_new<Shop1Material>();
        material->Initialise();
        SetMaterial(material);
    }

    void Shop1::Update()
    {
        Model::Update();
    }
}