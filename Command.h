#ifndef Command_h
#define Command_h

#include "Arduino.h"

class Command
{
public:
    static Command parse(char *str);
    static Command parse(char *str, char *buffer, int16_t bufferSize);
    int8_t getCommandSize();
    char *get(int8_t i);

private:
    Command(char *buffer, int8_t _commandSize);
    char *_buffer;
    int8_t _commandSize;
};

#endif