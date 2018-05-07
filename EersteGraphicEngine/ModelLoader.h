#pragma once

#include "PrerequisitesCore.h"
#include "VertexDesc.h"

namespace ege
{
    struct ModelDesc
    {
        Vector<VertexDesc>   Vertices;
        Vector<WORD>         Indices;
        bool                 HasColor;
        bool                 HasMaterial;

        ModelDesc()
            : HasMaterial(false)
            , HasColor(true)
        {}
    };

    class ModelLoader
    {
    public:
        ModelLoader() {};
        ~ModelLoader() {};

        void Load(String filePath, SPtr<ModelDesc> modelDesc);
    };
}