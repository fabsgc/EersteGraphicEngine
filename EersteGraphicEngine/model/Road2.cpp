#include "Road2.h"

#include "ModelManager.h"
#include "Road2Material.h"

namespace ege
{
    Road2::Road2()
        : Model()
    {
    }

    Road2::~Road2()
    {
    }

    void Road2::Initialise()
    {
        Build(gModelManager().GetPtr("road-2"));

        SPtr<Road2Material> material = ege_shared_ptr_new<Road2Material>();
        material->Initialise();
        SetMaterial(material);
    }

    void Road2::Update()
    {
        Model::Update();
    }
}