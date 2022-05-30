#include "monitor.h"

// A Simple wrapper for screen's displaying and flush
size_t d_printf(const char *format, ...)
{
    va_list va;
    size_t r;
    va_start(va, format);
    r = display.printf(format, va);
    va_end(va);
    display.display();
    return r;
}

size_t c_printf(const char *format, ...)
{
    va_list va;
    size_t r;
    va_start(va, format);
    r = display.printf(format, va);
    va_end(va);
    return r;
}