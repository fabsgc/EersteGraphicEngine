#include "MaterialManager.h"

namespace ege
{
    void MaterialManager::OnStartUp()
    {
        Initialise();
    }

    void MaterialManager::OnShutDown()
    {
    }

    void MaterialManager::Initialise()
    {
#if defined(EGE_MATERIAL_FOLDER) && defined(EGE_CONFIG_MATERIAL_FILE)
        tinyxml2::XMLDocument document;
        document.LoadFile(EGE_CONFIG_MATERIAL_FILE);

        tinyxml2::XMLElement* materialsElement = document.FirstChildElement("materials");
        EGE_ASSERT_ERROR((materialsElement != nullptr), "Material file malformed");

        for (tinyxml2::XMLElement* materialElement = materialsElement->FirstChildElement("material"); materialElement != nullptr; materialElement = materialElement->NextSiblingElement())
        {
        }
#endif
    }

    MaterialManager& gMaterialManager()
    {
        return static_cast<MaterialManager&>(MaterialManager::Instance());
    }

    MaterialManager* gMaterialManagerPtr()
    {
        return static_cast<MaterialManager*>(MaterialManager::InstancePtr());
    }
}