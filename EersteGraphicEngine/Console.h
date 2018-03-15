#pragma once

#include <fcntl.h>
#include <io.h>

#if defined(EGE_DEBUG)
#   ifndef EGE_ENABLE_CONSOLE
#   define EGE_ENABLE_CONSOLE()                                             \
        {                                                                   \
            AllocConsole();                                                 \
                                                                            \
            HANDLE handle_out = GetStdHandle(STD_OUTPUT_HANDLE);            \
            int hCrt = _open_osfhandle((intptr_t)handle_out, _O_TEXT);      \
            FILE* hf_out = _fdopen(hCrt, "w");                              \
            setvbuf(hf_out, NULL, _IONBF, 1);                               \
            *stdout = *hf_out;                                              \
                                                                            \
            HANDLE handle_in = GetStdHandle(STD_INPUT_HANDLE);              \
            hCrt = _open_osfhandle((intptr_t)handle_in, _O_TEXT);           \
            FILE* hf_in = _fdopen(hCrt, "r");                               \
            setvbuf(hf_in, NULL, _IONBF, 128);                              \
            *stdin = *hf_in;                                                \
                                                                            \
            FILE *fpstdin = stdin, *fpstdout = stdout, *fpstderr = stderr;  \
                                                                            \
            freopen_s(&fpstdin, "CONIN$", "r", stdin);                      \
            freopen_s(&fpstdout, "CONOUT$", "w", stdout);                   \
            freopen_s(&fpstderr, "CONOUT$", "w", stderr);                   \
        }
#   endif

#   ifndef EGE_FREE_CONSOLE
#   define EGE_FREE_CONSOLE()                                               \
        {                                                                   \
            FreeConsole();                                                  \
        }
#   endif
#else
#   define EGE_ENABLE_CONSOLE()
#   define EGE_FREE_CONSOLE()
#endif