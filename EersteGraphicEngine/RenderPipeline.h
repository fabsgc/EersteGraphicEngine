#pragma once

#include "PrerequisitesCore.h"
#include "RenderAPI.h"
#include "IDrawable.h"
#include "IUpdatable.h"
#include "Window.h"
#include "Scene.h"

namespace ege
{
    class RenderPipeline : public IDrawable, public IUpdatable
    {
    public:
        RenderPipeline();
        virtual ~RenderPipeline() {};

        virtual void Initialise(SPtr<Scene> scene);
        virtual void Draw() = 0;
        virtual void Update() = 0;
        virtual void OnResize() = 0;

    protected:
        RenderAPI&  _renderAPI;
        Window&     _window;
        SPtr<Scene> _scene;

        UINT        _width;
        UINT        _height;
    };
}