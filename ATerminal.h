#ifndef ATerminal_h
#define ATerminal_h

#include "Arduino.h"


class ATerminal
{
public:
    ATerminal(Stream *serial, char *buffer, int16_t bufferLen, char *term = "\r\n");

private:
    Stream *_serial;
    char *_buffer;
    int16_t _bufferLen;
    char *_term;
};

#endif