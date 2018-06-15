#include "Road1.h"

#include "ModelManager.h"
#include "Road1Material.h"

namespace ege
{
    Road1::Road1()
        : Model()
    {
    }

    Road1::~Road1()
    {
    }

    void Road1::Initialise()
    {
        Build(gModelManager().GetPtr("road-1"));

        SPtr<Road1Material> material = ege_shared_ptr_new<Road1Material>();
        material->Initialise();
        SetMaterial(material);
    }

    void Road1::Update()
    {
        Model::Update();
    }
}