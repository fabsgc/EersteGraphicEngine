#pragma once

#include "PrerequisitesCore.h"
#include "IComponentHandler.h"
#include "CoreApplication.h"
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

    struct InputMap
    {
        Key* KeyPtr;
        String Handler;
        JoypadButton* ButtonPtr;
        InputHandlerState State;

        InputMap(Key* key, JoypadButton* button, String handler)
            : KeyPtr(key)
            , ButtonPtr(button)
            , Handler(handler)
            , State(InputHandlerState::RELEASED)
        {}

        bool operator==(const InputMap& inputMap) const
        {
            return inputMap.Handler == Handler;
        }
    };

    class InputHandler : public IModule<InputHandler>, public IComponent, public IComponentHandler
    {
    public:
        InputHandler();
        ~InputHandler() {}
        InputHandlerState GetState(const String& handler);

    private:
        void Update(InputMap* inputMap);
        void OnStartUp() override;
        void OnShutDown() override;

    private:
        Map<Context, Vector<InputMap>> _handlers;
    };

    InputHandler&      gInputHandler();
    SPtr<InputHandler> gInputHandlerPtr();
}