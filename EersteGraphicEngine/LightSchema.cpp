#include "LightSchema.h"

#include "ModelManager.h"
#include "DefaultMaterial.h"

namespace ege
{
    LightSchema::LightSchema(String name)
        : Model()
        , _name(name)
    {
    }

    LightSchema::~LightSchema()
    {
    }

    void LightSchema::Initialise()
    {
        Build(gModelManager().GetPtr(_name));

        SPtr<DefaultMaterial> material = ege_shared_ptr_new<DefaultMaterial>();
        material->Initialise();
        SetMaterial(material);
    }
}