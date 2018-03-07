#include "InputHandler.h"

namespace ege
{
    InputHandler::InputHandler()
        : IComponent(ComponentType::INPUT_HANDLER)
    {
    }

    InputHandlerState InputHandler::GetState(const String& handler)
    {
        InputMap* inputMap = nullptr;

        for (auto itHandler = _handlers.begin(); itHandler != _handlers.end(); itHandler++)
        {
            const Context& context = itHandler->first;

            if (context == *gCoreApplication().GetCurrentContext())
            {
                Vector<InputMap>& inputMaps = itHandler->second;

                for (auto itMap = inputMaps.begin(); itMap != inputMaps.end(); itMap++)
                {
                    if (itMap->Handler == handler)
                    {
                        Update(&*itMap);
                        return itMap->State;
                    }
                }
            }
        }

        EGE_ASSERT_ERROR(false, ("This handler does not exist (" + handler + ")"));

        return InputHandlerState::RELEASED;
    }

    void InputHandler::Update(InputMap* inputMap)
    {
        Joypad& joypad = gJoypad();
        bool triggered = false;

        if (inputMap->KeyPtr != nullptr)
        {
            if (inputMap->KeyPtr->State == KeyState::TRIGGERED)
            {
                triggered = true;
            }
        }

        if (joypad.IsConnected() && inputMap->ButtonPtr != nullptr)
        {

            if (inputMap->ButtonPtr->State == JoypadButtonState::TRIGGERED)
            {
                triggered = true;
            }
        }

        inputMap->State = (triggered) ?InputHandlerState::TRIGGERED : InputHandlerState::RELEASED;
    }

    void InputHandler::OnStartUp()
    {
        InsertComponent(gKeyboard());
        InsertComponent(gJoypad());

        Keyboard& keyboard = static_cast<Keyboard&>(GetComponent(ComponentType::KEYBOARD));
        Joypad& joypad     = static_cast<Joypad&>(GetComponent(ComponentType::JOYPAD));

#ifdef EGE_CONFIG_KEYMAP_FILE
        tinyxml2::XMLDocument document;
        document.LoadFile(EGE_CONFIG_KEYMAP_FILE);

        tinyxml2::XMLElement* contextsElement = document.FirstChildElement("keymap");
        EGE_ASSERT_ERROR((contextsElement != nullptr), "Keymap file malformed");

        for (tinyxml2::XMLElement* contextElement = contextsElement->FirstChildElement("context"); contextElement != nullptr; contextElement = contextElement->NextSiblingElement())
        {
            Context context(contextElement->Attribute("name"));
            Vector<InputMap> inputMaps;

            for (tinyxml2::XMLElement* inputElement = contextElement->FirstChildElement("input"); inputElement != nullptr; inputElement = inputElement->NextSiblingElement())
            {
                String keyLabel    = inputElement->Attribute("key");
                String buttonLabel = inputElement->Attribute("button");
                String handler     = inputElement->Attribute("handler");

                InputMap inputMap(handler);

                if (keyLabel != "")
                {
                    inputMap.KeyPtr = &keyboard.GetKey(keyLabel);
                }

                if (buttonLabel != "")
                {
                    inputMap.ButtonPtr = &joypad.GetJoypadButton(buttonLabel);
                }

                inputMaps.push_back(inputMap);
            }

            _handlers[context] = inputMaps;
        }
#else
        EGE_ASSERT_ERROR_SHORT("Keymap file path not found");
#endif
    }

    void InputHandler::OnShutDown()
    {
    }

    InputHandler& gInputHandler()
    {
        return static_cast<InputHandler&>(InputHandler::Instance());
    }

    SPtr<InputHandler> gInputHandlerPtr()
    {
        return ege_shared_ptr(static_cast<InputHandler*>(InputHandler::InstancePtr()));
    }
}