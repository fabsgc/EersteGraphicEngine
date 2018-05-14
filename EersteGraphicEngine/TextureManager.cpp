#include "TextureManager.h"

namespace ege
{
    void TextureManager::OnStartUp()
    {
        Initialise();
    }

    void TextureManager::OnShutDown()
    {
    }

    void TextureManager::Initialise()
    {
#if defined(EGE_TEXTURE_FOLDER) && defined(EGE_CONFIG_TEXTURE_FILE)
        tinyxml2::XMLDocument document;
        document.LoadFile(EGE_CONFIG_TEXTURE_FILE);

        tinyxml2::XMLElement* texturesElement = document.FirstChildElement("textures");
        EGE_ASSERT_ERROR((texturesElement != nullptr), "Texture file malformed");

        for (tinyxml2::XMLElement* textureElement = texturesElement->FirstChildElement("texture"); textureElement != nullptr; textureElement = textureElement->NextSiblingElement())
        {
            String name = textureElement->Attribute("name");
            String filePath = textureElement->Attribute("file");

            SPtr<Texture> texture = ege_shared_ptr_new<Texture>(EGE_TEXTURE_FOLDER + filePath);
            texture->Initialise();
            Insert(name, texture);
        }
#endif
    }

    TextureManager& gTextureManager()
    {
        return static_cast<TextureManager&>(TextureManager::Instance());
    }

    TextureManager* gTextureManagerPtr()
    {
        return static_cast<TextureManager*>(TextureManager::InstancePtr());
    }
}