#pragma once

#include "PrerequisitesCore.h"
#include "IUpdatable.h"
#include "IDrawable.h"
#include "VertexDesc.h"

namespace ege
{
    class Geometry: IUpdatable, IDrawable
    {
    public:
        Geometry() {};
        ~Geometry() {};

        HRESULT Build();
        void    Update() override;
        void    Draw() override;

    private:
        Vector<VertexDesc> _vertices;
        Vector<WORD>       _indices;
        ID3D11Buffer*      _pVertexBuffer;
        ID3D11Buffer*      _pIndexBuffer;
    };
}