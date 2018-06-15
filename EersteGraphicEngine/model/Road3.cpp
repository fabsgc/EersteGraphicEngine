#include "Road3.h"

#include "ModelManager.h"
#include "Road3Material.h"

namespace ege
{
    Road3::Road3()
        : Model()
    {
    }

    Road3::~Road3()
    {
    }

    void Road3::Initialise()
    {
        Build(gModelManager().GetPtr("road-3"));

        SPtr<Road3Material> material = ege_shared_ptr_new<Road3Material>();
        material->Initialise();
        SetMaterial(material);
    }

    void Road3::Update()
    {
        Model::Update();
    }
}