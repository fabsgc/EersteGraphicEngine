#pragma once

#include "IComponentHandler.h"
#include "CoreApplication.h"
#include "IComponent.h"
#include "Keyboard.h"
#include "Joypad.h"
#include "Mouse.h"

namespace ege
{
    enum class InputHandlerState
    {
        TRIGGERED, RELEASED
    };

    enum class InputHandlerSwitchedState
    {
        YES, NO
    };

    struct InputMap
    {
        Vector<Key*> KeyPtrs;
        String Handler;
        Vector<JoypadButton*> ButtonPtrs;
        InputHandlerState State;
        InputHandlerSwitchedState Switched;

        InputMap(const String& handler)
            : Handler(handler)
            , State(InputHandlerState::RELEASED)
            , Switched(InputHandlerSwitchedState::NO)
        {}

        bool operator==(const InputMap& inputMap) const
        {
            return inputMap.Handler == Handler;
        }
    };

    struct InputState
    {
        InputHandlerState State;
        InputHandlerSwitchedState Switched;

        InputState()
            : State(InputHandlerState::RELEASED)
            , Switched(InputHandlerSwitchedState::NO)
        {}

        InputState(const InputMap& map)
            : State(map.State)
            , Switched(map.Switched)
        {}
    };

    class InputHandler : public IModule<InputHandler>, public IComponent, public IComponentHandler
    {
    public:
        InputHandler();
        ~InputHandler() {}
        const InputState GetState(const String& handler);

    private:
        void Update(InputMap* inputMap);
        void OnStartUp() override;
        void OnShutDown() override {};

    private:
        Map<Context, Vector<InputMap>> _handlers;
        CoreApplication&               _coreApplication;
    };

    InputHandler&      gInputHandler();
    SPtr<InputHandler> gInputHandlerPtr();
}