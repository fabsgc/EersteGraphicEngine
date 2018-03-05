#pragma once

#include "PrerequisitesCore.h"
#include "IComponentHandler.h"
#include "IComponent.h"
#include "IModule.h"
#include "Keyboard.h"
#include "Joypad.h"
#include "Mouse.h"

namespace ege
{
    enum class InputHandlerState
    {
        TRIGGERED, RELEASED
    };

    class InputHandler : public IModule<InputHandler>, public IComponent, public IComponentHandler
    {
    public:
        InputHandler();
        ~InputHandler() {}
        void Update(float deltaTime);
        InputHandlerState GetState();

    private:
        void OnStartUp() override;
        void OnShutDown() override;

    private:
    };

    InputHandler&      gInputHandler();
    SPtr<InputHandler> gInputHandlerPtr();
}