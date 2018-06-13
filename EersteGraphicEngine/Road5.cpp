#include "Road5.h"

#include "ModelManager.h"
#include "Road5Material.h"

namespace ege
{
    Road5::Road5()
        : Model()
    {
    }

    Road5::~Road5()
    {
    }

    void Road5::Initialise()
    {
        Build(gModelManager().GetPtr("road-5"));

        SPtr<Road5Material> material = ege_shared_ptr_new<Road5Material>();
        material->Initialise();
        SetMaterial(material);
    }

    void Road5::Update()
    {
        Model::Update();
    }
}