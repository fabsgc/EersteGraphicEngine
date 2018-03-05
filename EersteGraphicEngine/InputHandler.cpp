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

        for (auto it = _handlers.begin(); it != _handlers.end(); it++)
        {
            const Context& context = it->first;

            if (context == *gCoreApplication().GetCurrentContext())
            {
                Vector<InputMap>& inputMaps = it->second;

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

        EGE_ASSERT_ERROR(false,( "This handler does not exist (" + handler + ")"));
    }

    void InputHandler::Update(InputMap* inputMap)
    {
        //TODO
    }

    void InputHandler::OnStartUp()
    {
        //TODO
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