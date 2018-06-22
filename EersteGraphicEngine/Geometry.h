#pragma once

#include "PrerequisitesCore.h"
#include "IUpdatable.h"
#include "IDrawable.h"
#include "RenderAPI.h"
#include "VertexDesc.h"
#include "Color.h"

namespace ege
{
    class Geometry: IUpdatable, IDrawable
    {
    public:
        Geometry();
        ~Geometry();

        void Build(SPtr<ModelDesc> modelDesc = nullptr);
        void Update() override;
        void Draw() override;
        void SetColor(const Color color);

    protected:
        RenderAPI&         _renderAPI;

        Vector<VertexDesc> _vertices;
        Vector<WORD>       _indices;
        ID3D11Buffer*      _vertexBuffer;
        ID3D11Buffer*      _indexBuffer;
    };
}