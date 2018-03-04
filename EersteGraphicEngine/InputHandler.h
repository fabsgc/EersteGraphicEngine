#pragma once

#include "PrerequisitesCore.h"
#include "IComponentHandler.h"
#include "IComponent.h"
#include "Keyboard.h"
#include "Joypad.h"
#include "Mouse.h"

namespace ege
{
    class InputHandler : public IComponent, public IComponentHandler
    {
    public:
        InputHandler();
        ~InputHandler() {}
        void Update(float deltaTime);
        bool IsInputTriggered();

    private:
        void OnStartUp() override;
        void OnShutDown() override;

    private:
    };

    InputHandler&      gInputHandler();
    SPtr<InputHandler> gInputHandlerPtr();
}