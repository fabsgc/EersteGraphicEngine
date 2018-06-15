#include "House1.h"

#include "ModelManager.h"
#include "House1Material.h"

namespace ege
{
    House1::House1()
        : Model()
    {
    }

    House1::~House1()
    {
    }

    void House1::Initialise()
    {
        Build(gModelManager().GetPtr("house-1"));

        SPtr<House1Material> material = ege_shared_ptr_new<House1Material>();
        material->Initialise();
        SetMaterial(material);
    }

    void House1::Update()
    {
        Model::Update();
    }
}