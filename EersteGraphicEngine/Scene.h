#pragma once

#include "PrerequisitesCore.h"
#include "AmbientLight.h"
#include "IUpdatable.h"
#include "IDrawable.h"
#include "RenderAPI.h"
#include "Camera.h"
#include "Node.h"

namespace ege
{
    class Scene: public IDrawable, public IUpdatable
    {
    public:
        Scene();
        ~Scene();

        void                      Initialise();
        void                      InsertNode(String name, SPtr<Node> node);
        void                      InsertLight(String name, SPtr<Light> light);
        void                      InsertCamera(String name, SPtr<Camera> camera);
        //SPtr<Node>&               GetNode(String name);
        SPtr<Light>&              GetLight(String name);
        SPtr<Camera>&             GetCamera(String name);
        SPtr<Camera>&             GetActiveCamera();
        SPtr<AmbientLight>&       GetAmbientLight();
        Map<String, SPtr<Node>>&  GetNodes();
        Map<String, SPtr<Light>>& GetLights();
        void                      SetActiveCamera(SPtr<Camera> camera);
        void                      SetAmbientLight(SPtr<AmbientLight> ambientLight);
        void                      Update() override;
        void                      Draw() override;
        void                      DrawMetaData();
        void                      DrawCamera();
        void                      DrawLights();
        void                      DrawNodes();
        void                      DrawMetaDataLights();
        void                      DrawMetaDataNodes();

		void                      CreateDrawList();
		void                      CreateDrawListFromNode(SPtr<Node> node);

    protected:
        RenderAPI&                _renderAPI;

        //Map<String, SPtr<Node>> _nodes;
		Map<String, SPtr<Model>>  _models;
        Map<String, SPtr<Light>>  _lights;
        Map<String, SPtr<Camera>> _cameras;
        SPtr<Camera>              _camera;
        SPtr<AmbientLight>        _ambientLight;
    };
}