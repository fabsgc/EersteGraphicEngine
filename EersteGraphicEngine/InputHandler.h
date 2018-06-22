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

    struct KeyCombination
    {
        Vector<Key*> KeyPtrs;
    };

    struct JoypadButtonCombination
    {
        Vector<JoypadButton*> ButtonPtrs;
    };

    struct InputMap
    {
        String Handler;
        Vector<KeyCombination> Keys;
        Vector<JoypadButtonCombination> Buttons;
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

    protected:
        void Update(InputMap* inputMap);
        void OnStartUp() override;
        void OnShutDown() override {};

    protected:
        Map<Context, Vector<Vector<InputMap>>> _handlers;
        CoreApplication&                       _coreApplication;
    };

    InputHandler&      gInputHandler();
    SPtr<InputHandler> gInputHandlerPtr();
}