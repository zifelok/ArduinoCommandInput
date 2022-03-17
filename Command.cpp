#include "Command.h"

Command Command::parse(char *str)
{
    return Command(str, 0);
}

Command Command::parse(char *str, char *buffer, int16_t bufferSize)
{
    return Command(str, 0);
}

Command::Command(char *buffer, int8_t commandSize)
{
    _buffer = buffer;
    _commandSize = commandSize;
}

int8_t Command::getCommandSize()
{
    return _commandSize;
}

char *Command::get(int8_t i)
{
    if (i < 0 || i >= _commandSize)
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