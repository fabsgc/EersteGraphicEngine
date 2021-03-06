#pragma once

#include "PrerequisitesCore.h"
#include "CoreApplication.h"
#include "RenderAPI.h"
#include "Geometry.h"
#include "Node.h"

namespace ege
{
    enum class LightMode
    {
        All, None, Selected
    };

    class Model: public Node
    {
    public:
        Model();
        ~Model();

        void                 Initialise() override;
        void                 Update() override;
        void                 Draw() override;
        void                 DrawMetaData() override;
        void                 Build(SPtr<ModelDesc> modelDesc);
        void                 SetMaterial(SPtr<Material> material);
        void                 SetColor(const Color color);
		void                 SetCastShadow(bool castShadow);
        void                 SetLightMode(LightMode lightMode);
        void                 AddLights(SPtr<Light> light);
        Geometry&            GetGeometry();
		SPtr<Material>       GetMaterial();
		SPtr<ModelDesc>      GetModelDesc();
        bool                 GetCastShadow() const;
        const LightMode&     GetLightMode() const;
        Vector<SPtr<Light>>& GetLights();

	protected:
		bool                 IsInFrustum();

    protected:
		static const bool      DefaultCastShadow;
        static const LightMode DefaultLightMode;
        
    protected:
        RenderAPI&          _renderAPI;
		CoreApplication&    _application;
		Scene&              _scene;

        SPtr<ModelDesc>     _modelDesc;
        SPtr<Material>      _material;
        Geometry            _geometry;

        bool                _castShadow;
        LightMode           _lightMode;
        Vector<SPtr<Light>> _lights;
    };
}