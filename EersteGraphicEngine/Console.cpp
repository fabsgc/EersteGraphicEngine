#include "Console.h"

namespace ege
{
    void Console::OnStartUp()
    {
#if defined(EGE_DEBUG)
        AllocConsole();
        AttachConsole(GetCurrentProcessId());

        HANDLE handle_out = GetStdHandle(STD_OUTPUT_HANDLE);
        _hCrtOut = _open_osfhandle((intptr_t)handle_out, _O_TEXT);
        FILE* hf_out = _fdopen(_hCrtOut, "w");
        setvbuf(hf_out, NULL, _IONBF, 1);
        *stdout = *hf_out;

        FILE *fpstdout = stdout, *fpstderr = stderr;

        freopen_s(&fpstdout, "CONOUT$", "w", stdout);
        freopen_s(&fpstderr, "CONOUT$", "w", stderr);
#endif
    }

    void Console::OnShutDown()
    {
#if defined(EGE_DEBUG)
#endif
    }

    Console& gConsole()
    {
        return static_cast<Console&>(Console::Instance());
    }
}