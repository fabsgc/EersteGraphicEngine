#include "Application.h"

using namespace ege;

int CALLBACK WinMain(_In_  HINSTANCE hInstance, _In_  HINSTANCE hPrevInstance, _In_  LPSTR lpCmdLine, _In_  int nCmdShow)
{
    StartUpDescription desc;

    desc.MaxFPS            = 60;
    desc.WindowDesc.Width  = 960;
    desc.WindowDesc.Height = 540;
    desc.WindowDesc.Title  = String("My Application");

    Application::StartUp(desc);
    Application& app = gApplication();

    app.RunMainLoop();
    app.ShutDown();

    return 0;
}