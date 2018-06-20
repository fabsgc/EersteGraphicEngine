#include "LightModel.h"

#include "ModelManager.h"
#include "DefaultMaterial.h"

namespace ege
{
    LightModel::LightModel(String name)
        : Model()
        , _name(name)
    {
    }

    LightModel::~LightModel()
    {
    }

    void LightModel::Initialise()
    {
        Build(gModelManager().GetPtr(_name));

        SPtr<DefaultMaterial> material = ege_shared_ptr_new<DefaultMaterial>();
        material->Initialise();
        SetMaterial(material);
    }
}