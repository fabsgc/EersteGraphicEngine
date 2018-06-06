#include "ShaderManager.h"
#include "Shader.h"

namespace ege
{
    void ShaderManager::OnStartUp()
    {
        Initialise();
    }

    void ShaderManager::OnShutDown()
    {
    }

    void ShaderManager::Initialise()
    {
#if defined(EGE_SHADERS_FOLDER) && defined(EGE_CONFIG_SHADER_FILE)
        tinyxml2::XMLDocument document;
        document.LoadFile(EGE_CONFIG_SHADER_FILE);

        tinyxml2::XMLElement* shadersElement = document.FirstChildElement("shaders");
        EGE_ASSERT_ERROR((shadersElement != nullptr), "Shader file malformed");

        for (tinyxml2::XMLElement* shaderProgramElement = shadersElement->FirstChildElement("shader-program"); shaderProgramElement != nullptr; shaderProgramElement = shaderProgramElement->NextSiblingElement())
        {
            ShaderConfig config;
            config.Name = shaderProgramElement->Attribute("name");
            config.IncludeDirectory = shaderProgramElement->Attribute("include-path");
            
            for (tinyxml2::XMLElement* shaderElement = shaderProgramElement->FirstChildElement("shader"); shaderElement != nullptr; shaderElement = shaderElement->NextSiblingElement())
            {
                String type = shaderElement->Attribute("type");
                String file = shaderElement->Attribute("file");

                if (file != "")
                {
                    if (type == "vertex-shader")
                    {
                        config.VertexShaderPath = EGE_SHADERS_FOLDER + file;
                    }
                    else if (type == "hull-shader")
                    {
                        config.HullShaderPath = EGE_SHADERS_FOLDER + file;
                    }
                    else if (type == "domain-shader")
                    {
                        config.DomainShaderPath = EGE_SHADERS_FOLDER + file;
                    }
                    else if (type == "geometry-shader")
                    {
                        config.GeometryShaderPath = EGE_SHADERS_FOLDER + file;
                    }
                    else if (type == "pixel-shader")
                    {
                        config.PixelShaderPath = EGE_SHADERS_FOLDER + file;
                    }
                }
            }

            SPtr<Shader> shader = ege_shared_ptr_new<Shader>(config);
            shader->Initialise();
            Insert(config.Name, shader);
        }
#endif
    }

    ShaderManager& gShaderManager()
    {
        return static_cast<ShaderManager&>(ShaderManager::Instance());
    }

    ShaderManager* gShaderManagerPtr()
    {
        return static_cast<ShaderManager*>(ShaderManager::InstancePtr());
    }
}