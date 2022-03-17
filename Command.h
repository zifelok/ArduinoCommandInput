#ifndef Command_h
#define Command_h

#include "Arduino.h"

class Command
{
public:
    static Command parse(char *str);
    static Command parse(char *str, char *buffer, uint16_t bufferSize);
    uint8_t getCommandSize();
    char *get(uint8_t i);

private:
    Command(char *buffer, uint8_t _commandSize);
    char *_buffer;
    uint8_t _commandSize;
};

#endif