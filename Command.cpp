#include "Command.h"

Command Command::parse(char *str)
{
    return Command(str, 0);
}

Command Command::parse(char *str, char *buffer, uint16_t bufferSize)
{
    return Command(str, 0);
}

Command::Command(char *buffer, uint8_t commandSize)
{
    _buffer = buffer;
    _commandSize = commandSize;
}

uint8_t Command::getCommandSize()
{
    return _commandSize;
}

char *Command::get(uint8_t i)
{
    if (i >= _commandSize)
        return NULL;
    char *c = _buffer;
    while (i > 0)
    {
        while (*c != '\0')
            c++;
        while (*c == '\0')
            c++;
        --i;
    }
    return c;
}