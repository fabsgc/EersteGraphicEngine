#pragma once

#include "PrerequisitesCore.h"
#include "VertexDesc.h"

namespace ege
{
    struct ModelDesc
    {
        std::vector<VertexDesc>   Vertices;
        std::vector<WORD>         Indices;
        bool                      HasColor;

        ModelDesc()
            : HasColor(false)
        {}
    };

    class ModelLoader
    {
    public:
        ModelLoader() {};
        ~ModelLoader() {};

        void Load(String fileName, ModelDesc& meshDatas);
    };
}