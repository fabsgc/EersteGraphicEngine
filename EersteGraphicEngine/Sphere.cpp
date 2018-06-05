#include "Sphere.h"

#include "ModelManager.h"
#include "SphereMaterial.h"

namespace ege
{
    Sphere::Sphere()
        : Model()
    {
    }

    Sphere::~Sphere()
    {
    }

    void Sphere::Initialise()
    {
        Build(gModelManager().GetPtr("sphere"));

        SPtr<SphereMaterial> material = ege_shared_ptr_new<SphereMaterial>();
        material->Initialise();
        material->SetSpecularPower(16.0f);
        SetMaterial(material);
    }

    void Sphere::Update()
    {
        Model::Update();
    }
}