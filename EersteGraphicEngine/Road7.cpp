#include "Road7.h"

#include "ModelManager.h"
#include "Road7Material.h"

namespace ege
{
    Road7::Road7()
        : Model()
    {
    }

    Road7::~Road7()
    {
    }

    void Road7::Initialise()
    {
        Build(gModelManager().GetPtr("road-7"));

        SPtr<Road7Material> material = ege_shared_ptr_new<Road7Material>();
        material->Initialise();
        SetMaterial(material);
    }

    void Road7::Update()
    {
        Model::Update();
    }
}