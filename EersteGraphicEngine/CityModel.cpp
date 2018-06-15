#include "ModelManager.h"
#include "CityModel.h"
#include "CityMaterial.h"

namespace ege
{
    CityModel::CityModel(String modelName, String diffuseName, String specularName)
        : Model()
        , _modelName(modelName)
        , _diffuseName(diffuseName)
        , _specularName(specularName)
    {
    }

    CityModel::~CityModel()
    {
    }

    void CityModel::Initialise()
    {
        Build(gModelManager().GetPtr(_modelName));

        SPtr<CityMaterial> material = ege_shared_ptr_new<CityMaterial>(_diffuseName, _specularName);
        material->Initialise();
        SetMaterial(material);
    }

    void CityModel::Update()
    {
        Model::Update();
    }
}