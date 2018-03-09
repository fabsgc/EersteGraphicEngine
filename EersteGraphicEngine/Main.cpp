#include "CoreApplication.h"
#include <windows.h>

using namespace ege;

int CALLBACK WinMain(_In_  HINSTANCE hInstance, _In_  HINSTANCE hPrevInstance, _In_  LPSTR lpCmdLine, _In_  int nCmdShow)
{
    START_UP_DESC desc;

    desc.MaxFPS            = 60;
    desc.WindowDesc.Width  = 960;
    desc.WindowDesc.Height = 540;
    desc.WindowDesc.Title  = String("My Application");

    CoreApplication::StartUp(desc);
    CoreApplication& app = gCoreApplication();

    app.RunMainLoop();
    app.ShutDown();

    return 0;
}