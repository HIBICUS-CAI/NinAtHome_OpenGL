#include "NinLog.h"

int VDebugPrintF(const char* format, va_list argList)
{
    const UINT32 MAX_CHARS = 1024;
    static char s_LogBuffer[MAX_CHARS];

    int charsWritten = vsnprintf(
        s_LogBuffer, MAX_CHARS, format, argList);

    OutputDebugString(s_LogBuffer);

    return charsWritten;
}

int DebugPrintF(const char* format, ...)
{
    va_list argList;
    va_start(argList, format);

    int charsWritten = VDebugPrintF(format, argList);

    va_end(argList);

    return charsWritten;
}
