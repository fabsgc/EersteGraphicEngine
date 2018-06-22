#pragma once

#include "PrerequisitesCore.h"
#include "RenderAPI.h"

namespace ege
{
    class Texture
    {
    public:
        Texture(String filePath);
        ~Texture();
        void Initialise();
        void Apply(UINT slot);

    protected:
        RenderAPI &               _renderAPI;
        String                    _filePath;
        ID3D11ShaderResourceView* _texture;
    };
}