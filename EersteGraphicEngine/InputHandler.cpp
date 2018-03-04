#include "InputHandler.h"

namespace ege
{
    InputHandler::InputHandler()
        : IComponent(ComponentType::INPUT_HANDLER)
    {
    }

    void InputHandler::Update(float deltaTime)
    {
        //TODO
    }

    bool InputHandler::IsInputTriggered()
    {
        //TODO
        return true;
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