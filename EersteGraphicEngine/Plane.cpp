#include "Plane.h"

#include "ModelManager.h"
#include "PlaneMaterial.h"

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

        SPtr<PlaneMaterial> material = ege_shared_ptr_new<PlaneMaterial>();
        material->Initialise();
        SetMaterial(material);
    }

    void Plane::Update()
    {
        Model::Update();
    }
}