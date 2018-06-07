#include "Sphere.h"

#include "ModelManager.h"
#include "DefaultMaterial.h"

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

        SPtr<DefaultMaterial> material = ege_shared_ptr_new<DefaultMaterial>();
        material->Initialise();
        SetMaterial(material);
    }

    void Sphere::Update()
    {
        Model::Update();
    }
}