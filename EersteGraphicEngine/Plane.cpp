#include "Plane.h"

#include "ModelManager.h"
#include "DefaultMaterial.h"

namespace ege
{
    Plane::Plane()
        : Model()
    {
    }

    Plane::~Plane()
    {
    }

    void Plane::Initialise()
    {
        Build(gModelManager().GetPtr("plane"));

        SPtr<DefaultMaterial> material = ege_shared_ptr_new<DefaultMaterial>();
        material->Initialise();
        SetMaterial(material);
    }

    void Plane::Update()
    {
        Model::Update();
    }
}